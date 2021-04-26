#ifndef RVUPHISTOGRAMFEATURE_H
#define RVUPHISTOGRAMFEATURE_H

#include <features/BaseFeature.h>
#include <nfiq2_fingerprintimagedata.hpp>
#include <nfiq2_interfacedefinitions.hpp>

#include <string>
#include <vector>

namespace NFIQ2 { namespace QualityFeatures {

static double RVUPHISTLIMITS[9] = { 0.5, 0.667, 0.8, 1, 1.25, 1.5, 2, 24, 30 };

class RVUPHistogramFeature : public BaseFeature {
    public:
	RVUPHistogramFeature(
	    const NFIQ2::FingerprintImageData &fingerprintImage);
	virtual ~RVUPHistogramFeature();

	std::string getModuleName() const override;

	static std::vector<std::string> getAllFeatureIDs();
	static const std::string speedFeatureIDGroup;
	static const std::string moduleName;

    private:
	std::vector<NFIQ2::QualityFeatureResult> computeFeatureData(
	    const NFIQ2::FingerprintImageData &fingerprintImage);

	const int blocksize { 32 };
	const double threshold { .1 };
	const int slantedBlockSizeX { 32 };
	const int slantedBlockSizeY { 16 };
	const bool padFlag { true };
};

}}

#endif

/******************************************************************************/
