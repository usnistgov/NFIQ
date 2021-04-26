#include <nfiq2_modelinfo.hpp>
#include <nfiq2_nfiq2algorithm.hpp>

#include "nfiq2_nfiq2algorithm_impl.hpp"

#ifdef EMBED_RANDOMFOREST_PARAMETERS
NFIQ2::NFIQ2Algorithm::NFIQ2Algorithm()
    : pimpl { new NFIQ2::NFIQ2Algorithm::Impl() }
{
}
#endif

NFIQ2::NFIQ2Algorithm::NFIQ2Algorithm(
    const std::string &fileName, const std::string &fileHash)
    : pimpl { new NFIQ2::NFIQ2Algorithm::Impl(fileName, fileHash) }
{
}

NFIQ2::NFIQ2Algorithm::NFIQ2Algorithm(const NFIQ2::ModelInfo &modelInfoObj)
    : NFIQ2::NFIQ2Algorithm { modelInfoObj.getModelPath(),
	    modelInfoObj.getModelHash() }
{
}

unsigned int
NFIQ2::NFIQ2Algorithm::computeQualityScore(
    const NFIQ2::FingerprintImageData &rawImage) const
{
	return (this->pimpl->computeQualityScore(rawImage));
}

unsigned int
NFIQ2::NFIQ2Algorithm::computeQualityScore(
    const std::vector<std::shared_ptr<NFIQ2::QualityFeatures::BaseFeature>>
	&features) const
{
	return (this->pimpl->computeQualityScore(features));
}

unsigned int
NFIQ2::NFIQ2Algorithm::computeQualityScore(
    const std::unordered_map<std::string, NFIQ2::QualityFeatureData> &features)
    const
{
	return (this->pimpl->computeQualityScore(features));
}

std::string
NFIQ2::NFIQ2Algorithm::getParameterHash() const
{
	return (this->pimpl->getParameterHash());
}

NFIQ2::NFIQ2Algorithm::~NFIQ2Algorithm() = default;
