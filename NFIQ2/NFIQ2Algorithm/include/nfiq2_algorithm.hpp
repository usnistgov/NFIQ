#ifndef NFIQ2_ALGORITHM_HPP_
#define NFIQ2_ALGORITHM_HPP_

#include <nfiq2_fingerprintimagedata.hpp>
#include <nfiq2_interfacedefinitions.hpp>
#include <nfiq2_modelinfo.hpp>
#include <nfiq2_qualityfeatures.hpp>

#include <memory>
#include <string>
#include <unordered_map>

namespace NFIQ2 {
/** Wrapper to return quality scores for a fingerprint image */
class Algorithm {
    public:
#ifdef NFIQ2_EMBED_RANDOM_FOREST_PARAMETERS
	Algorithm();
#endif
	Algorithm(const std::string &fileName, const std::string &fileHash);
	Algorithm(const NFIQ2::ModelInfo &modelInfoObj);
	~Algorithm();

	/**
	 * @fn computeQualityScore
	 * @brief Computes the quality score from the input fingerprint image
	 * data
	 * @param rawImage fingerprint image in raw format
	 * @return achieved quality score
	 */
	unsigned int computeQualityScore(
	    const NFIQ2::FingerprintImageData &rawImage) const;

	/**
	 * @fn computeQualityScore
	 * @brief Computes the quality score from a vector of extracted feature
	 * from a cropped fingerprint image
	 * @param features list of computed feature metrics that contain quality
	 * information for a fingerprint image
	 * @return achieved quality score
	 */
	unsigned int computeQualityScore(const std::vector<
	    std::shared_ptr<NFIQ2::QualityFeatures::BaseFeature>> &features)
	    const;

	/**
	 * @fn computeQualityScore
	 * @brief Computes the quality score from the extracted image
	 * quality feature data
	 * @param features map of string, quality feature data pairs
	 * @return achieved quality score
	 */
	unsigned int computeQualityScore(
	    const std::unordered_map<std::string, NFIQ2::QualityFeatureData>
		&features) const;

	/**
	 * @brief
	 * Obtain MD5 checksum of Random Forest parameter file loaded.
	 *
	 * @return
	 * MD5 checksum of the Random Forest parameter file loaded.
	 */
	std::string getParameterHash() const;

	/**
	 * @brief
	 * Obtain if the random forest parameters are embedded in the library
	 * or located externally.
	 *
	 * @return
	 * true if random forest parameters are embedded, false otherwise.
	 */
	bool isEmbedded() const;

    private:
	class Impl;
	const std::unique_ptr<const Algorithm::Impl> pimpl;

	Algorithm(const Algorithm &) = delete;
	Algorithm &operator=(const Algorithm &) = delete;
};
} // namespace NFIQ

#endif
