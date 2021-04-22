#include <features/FeatureFunctions.h>
#include <features/OFFeature.h>
#include <math.h>
#include <nfiq2_nfiqexception.hpp>
#include <nfiq2_timer.hpp>
#include <opencv2/core/core.hpp>

#include <sstream>

#if defined WINDOWS || defined WIN32
#include <float.h>
#include <windows.h>
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace NFIQ;

NFIQ::QualityFeatures::OFFeature::OFFeature(
    const NFIQ::FingerprintImageData &fingerprintImage)
{
	this->setFeatures(computeFeatureData(fingerprintImage));
}

NFIQ::QualityFeatures::OFFeature::~OFFeature() = default;

const std::string NFIQ::QualityFeatures::OFFeature::moduleName { "NFIQ2_OF" };
std::string
NFIQ::QualityFeatures::OFFeature::getModuleName() const
{
	return moduleName;
}

std::vector<std::string>
NFIQ::QualityFeatures::OFFeature::getAllFeatureIDs()
{
	std::vector<std::string> featureIDs;
	addHistogramFeatureNames(featureIDs, "OF_Bin10_", 10);

	return featureIDs;
}

const std::string NFIQ::QualityFeatures::OFFeature::speedFeatureIDGroup =
    "Orientation flow";

std::vector<NFIQ::QualityFeatureResult>
NFIQ::QualityFeatures::OFFeature::computeFeatureData(
    const NFIQ::FingerprintImageData &fingerprintImage)
{
	std::vector<NFIQ::QualityFeatureResult> featureDataList;

	// check if input image has 500 dpi
	if (fingerprintImage.m_ImageDPI != NFIQ::e_ImageResolution_500dpi) {
		throw NFIQ::NFIQException(NFIQ::e_Error_FeatureCalculationError,
		    "Only 500 dpi fingerprint images are supported!");
	}

	cv::Mat img;
	try {
		// get matrix from fingerprint image
		img = cv::Mat(fingerprintImage.m_ImageHeight,
		    fingerprintImage.m_ImageWidth, CV_8UC1,
		    (void *)fingerprintImage.data());
	} catch (cv::Exception &e) {
		std::stringstream ssErr;
		ssErr << "Cannot get matrix from fingerprint image: "
		      << e.what();
		throw NFIQ::NFIQException(
		    NFIQ::e_Error_FeatureCalculationError, ssErr.str());
	}

	NFIQ::Timer timerOF;
	double timeOF = 0.0;
	try {
		timerOF.start();

		int rows = img.rows;
		int cols = img.cols;

		const int v1sz_x = slantedBlockSizeX;
		const int v1sz_y = slantedBlockSizeY;

		cv::Mat maskim;
		ridgesegment(img, blocksize, threshold, cv::noArray(), maskim,
		    cv::noArray());

		// ----------
		// compute Of
		// ----------

		double blk = static_cast<double>(blocksize);

		double sumSQ = static_cast<double>(
		    (v1sz_x * v1sz_x) + (v1sz_y * v1sz_y));
		double eblksz = ceil(
		    sqrt(sumSQ)); // block size for extraction of slanted block
		double diff = (eblksz - blk);
		int blkoffset = static_cast<int>(
		    ceil(diff / 2)); // overlapping border

		int mapRows = static_cast<int>(
		    (static_cast<double>(rows) - diff) / blk);
		int mapCols = static_cast<int>(
		    (static_cast<double>(cols) - diff) / blk);

		cv::Mat maskBseg = cv::Mat::zeros(mapRows, mapCols, CV_8UC1);
		cv::Mat blkorient = cv::Mat::zeros(mapRows, mapCols, CV_64F);

		cv::Mat im_roi, blkwim;
		cv::Mat maskB1;
		double cova, covb, covc;
		// Image processed NOT from beg to end but with a border around
		// - can't be vectorized:(
		int br = 0;
		int bc = 0;

		for (int r = blkoffset; r < rows - (blocksize + blkoffset - 1);
		     r += blocksize) {
			for (int c = blkoffset;
			     c < cols - (blocksize + blkoffset - 1);
			     c += blocksize) {
				im_roi = img(
				    cv::Range(
					r, cv::min(r + blocksize, img.rows)),
				    cv::Range(
					c, cv::min(c + blocksize, img.cols)));
				maskB1 = maskim(
				    cv::Range(
					r, cv::min(r + blocksize, maskim.rows)),
				    cv::Range(c,
					cv::min(c + blocksize, maskim.cols)));
				maskBseg.at<uint8_t>(br, bc) = allfun(maskB1);
				covcoef(im_roi, cova, covb, covc,
				    CENTERED_DIFFERENCES);

				// ridge ORIENT local
				blkorient.at<double>(br, bc) = ridgeorient(
				    cova, covb, covc);
				bc = bc + 1;
			}
			br = br + 1;
			bc = 0;
		}

		// % get the diff of orient. angles from neighbouring blocks
		// loqall = blockproc(blkorient, [1 1], @orientangdiff,
		// 'BorderSize', [border border], 'TrimBorder', false); add a
		// border of zeros around the blkorient array, since the matlab
		// blockproc function pads with zeros at the edges.
		cv::Mat paddedBlkorient;
		copyMakeBorder(blkorient, paddedBlkorient, 1, 1, 1, 1,
		    cv::BORDER_CONSTANT, 0);

		// for each point in the original blkorient array, compute the
		// orientation angle difference with its immediate neighbors all
		// around.

		cv::Mat loqall(blkorient.rows, blkorient.cols, CV_64F);
		const double bsize = 9; // The center point plus its immediate
					// neighbors forms a 3x3 block

		for (int i = 1; i <= blkorient.rows; i++) {
			for (int j = 1; j <= blkorient.cols; j++) {
				// remember: OpenCV ranges are open-ended on the
				// upper end
				cv::Mat blkROI = paddedBlkorient(
				    cv::Range(i - 1, i + 2),
				    cv::Range(j - 1, j + 2));
				// Subtract the input block from the center
				// value and get its absolute value.
				cv::Mat blockAbsDiff;
				cv::Scalar centerVal = blkROI.at<double>(1, 1);
				absdiff(centerVal, blkROI, blockAbsDiff);
				cv::Scalar loq = sum(blockAbsDiff) /
				    (bsize - 1);
				loqall.at<double>(i - 1, j - 1) = loq.val[0];
			}
		}

		// angdiff     = deg2rad(90-angmin);
		// angmin      = deg2rad(angmin);
		// loqs        = zeros(size(loqall));
		const double Deg2Rad = M_PI / 180.0;
		const double PI4 = 90.0;
		double angdiff = (PI4 - angleMin) * Deg2Rad;
		double angmin = angleMin * Deg2Rad;

		// % overlapping window: if one of the surrouding blocks from
		// which the anglediff was computed % is in background, exclude
		// whole window from comp. maskBloqseg =
		// logical(blkproc(maskBseg, [1 1], [border border], allfun));
		cv::Mat paddedMaskBseg;
		copyMakeBorder(maskBseg, paddedMaskBseg, 1, 1, 1, 1,
		    cv::BORDER_CONSTANT, 0);
		cv::Mat maskBloqseg(maskBseg.rows, maskBseg.cols, CV_8UC1);
		for (int i = 1; i <= maskBseg.rows; i++) {
			for (int j = 1; j <= maskBseg.cols; j++) {
				cv::Mat blkROI = paddedMaskBseg(
				    cv::Range(i - 1, i + 2),
				    cv::Range(j - 1, j + 2));
				maskBloqseg.at<uint8_t>(i - 1, j - 1) = allfun(
				    blkROI);
			}
		}

		std::vector<double> dataVector;
		dataVector.reserve(loqall.rows * loqall.cols);

		// % (angle) mask - only blocks with angle change > angmin
		// maskBang = loqall > angmin;
		cv::Mat maskBang = loqall > angmin;
		// % (local orientation quality) mask of FOREGROUND blocks >
		// angmin deg maskBloq = maskBang & maskBloqseg;
		cv::Mat maskBloq = maskBang & maskBloqseg;
		// % map of local orientation quality scores
		// loqs(maskBloq) = (loqall(maskBloq) - angmin) ./ angdiff;
		cv::Mat loqs = cv::Mat::zeros(loqall.rows, loqall.cols, CV_64F);
		for (int i = 0; i < loqall.rows; i++) {
			for (int j = 0; j < loqall.cols; j++) {
				if (maskBloq.at<uint8_t>(i, j) == 1) {
					loqs.at<double>(
					    i, j) = (loqall.at<double>(i, j) -
							angmin) /
					    angdiff;
					dataVector.push_back(
					    loqs.at<double>(i, j));
				}
			}
		}

		// % global orientation flow quality score (GOQS) only from
		// FOREGROUND (all neighbouring) % blocks (background = 0) goqs
		// = mean(loqs(maskBloqseg)); orientationFlow = 1 - goqs; %NOTE
		// verify: maskBloqseg == true
		//  int totalNonZero = countNonZero(loqs);
		cv::Scalar goqs = mean(loqs, maskBloqseg);
		double OfScore = 0.0;
		if (goqs.val[0] > 0) {
			OfScore = 1.0 - goqs.val[0];
		}

		std::vector<double> histogramBins10;
		histogramBins10.push_back(OFHISTLIMITS[0]);
		histogramBins10.push_back(OFHISTLIMITS[1]);
		histogramBins10.push_back(OFHISTLIMITS[2]);
		histogramBins10.push_back(OFHISTLIMITS[3]);
		histogramBins10.push_back(OFHISTLIMITS[4]);
		histogramBins10.push_back(OFHISTLIMITS[5]);
		histogramBins10.push_back(OFHISTLIMITS[6]);
		histogramBins10.push_back(OFHISTLIMITS[7]);
		histogramBins10.push_back(OFHISTLIMITS[8]);
		addHistogramFeatures(featureDataList, "OF_Bin10_",
		    histogramBins10, dataVector, 10);

		timeOF = timerOF.stop();

		// Speed
		NFIQ::QualityFeatureSpeed speed;
		speed.featureIDGroup = OFFeature::speedFeatureIDGroup;

		addHistogramFeatureNames(speed.featureIDs, "OF_Bin10_", 10);

		speed.featureSpeed = timeOF;
		this->setSpeed(speed);

	} catch (cv::Exception &e) {
		std::stringstream ssErr;
		ssErr << "Cannot compute Orientation Flow (OF): " << e.what();
		throw NFIQ::NFIQException(
		    NFIQ::e_Error_FeatureCalculationError, ssErr.str());
	} catch (NFIQ::NFIQException &e) {
		throw e;
	} catch (...) {
		throw NFIQ::NFIQException(NFIQ::e_Error_FeatureCalculationError,
		    "Unknown exception occurred!");
	}
	return featureDataList;
}
