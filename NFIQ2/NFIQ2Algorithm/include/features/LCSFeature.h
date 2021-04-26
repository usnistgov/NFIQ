#ifndef LCSFEATURE_H
#define LCSFEATURE_H

#include <features/BaseFeature.h>
#include <nfiq2_fingerprintimagedata.hpp>
#include <nfiq2_interfacedefinitions.hpp>

#include <string>
#include <vector>

namespace NFIQ2 { namespace QualityFeatures {

static double LCSHISTLIMITS[9] = { 0, 0.70, 0.74, 0.77, 0.79, 0.81, 0.83, 0.85,
	0.87 };

class LCSFeature : public BaseFeature {
    public:
	LCSFeature(const NFIQ2::FingerprintImageData &fingerprintImage);
	virtual ~LCSFeature();

	std::string getModuleName() const override;

	static std::vector<std::string> getAllFeatureIDs();
	static const std::string speedFeatureIDGroup;
	static const std::string moduleName;

    private:
	std::vector<NFIQ2::QualityFeatureResult> computeFeatureData(
	    const NFIQ2::FingerprintImageData &fingerprintImage);

	const int blocksize { 32 };
	const double threshold { .1 };
	const int scannerRes { 500 };
	const bool padFlag { false };
};

}}

#endif

/******************************************************************************/
