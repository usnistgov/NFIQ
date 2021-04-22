#ifndef RANDOMFORESTML_H
#define RANDOMFORESTML_H

#include <nfiq2_interfacedefinitions.hpp>
#include <opencv2/core/version.hpp>
#include <stdlib.h>

#include <list>
#include <string>
#include <unordered_map>
#include <vector>
#if CV_MAJOR_VERSION <= 2
#include <opencv/cv.h>
#include <opencv/ml.h>
#else
#include <opencv2/ml.hpp>
#endif /* CV_MAJOR_VERSION */

#undef EMBED_RANDOMFOREST_PARAMETERS

namespace NFIQ { namespace Prediction {

class RandomForestML {
    public:
	RandomForestML();
	virtual ~RandomForestML();

	static const std::string moduleName;
	std::string getModuleName() const;

#ifdef EMBED_RANDOMFOREST_PARAMETERS
	std::string initModule();
#endif
	std::string initModule(
	    const std::string &fileName, const std::string &fileHash);

	void evaluate(
	    const std::unordered_map<std::string, NFIQ::QualityFeatureData>
		&features,
	    const double &utilityValue, double &qualityValue,
	    double &deviation) const;

    private:
#if CV_MAJOR_VERSION <= 2
	CvRTrees *m_pTrainedRF;
#else
	cv::Ptr<cv::ml::RTrees> m_pTrainedRF;
#endif

	std::string calculateHashString(const std::string &s);
	void initModule(const std::string &params);
#ifdef EMBED_RANDOMFOREST_PARAMETERS
	std::string joinRFTrainedParamsString();
#endif
};

}}

#endif

/******************************************************************************/
