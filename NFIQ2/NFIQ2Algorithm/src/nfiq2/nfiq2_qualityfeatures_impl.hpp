#ifndef NFIQ2_QUALITYFEATURES_IMPL_HPP_
#define NFIQ2_QUALITYFEATURES_IMPL_HPP_

#include <features/BaseFeature.h>
#include <nfiq2_fingerprintimagedata.hpp>
#include <nfiq2_qualityfeatures.hpp>

#include <list>
#include <memory>
#include <string>
#include <vector>

namespace NFIQ2 { namespace QualityFeatures { namespace Impl {

/**
 * @brief
 * Obtain all actionable quality feedback identifiers.
 *
 * @return
 * Vector of strings containing all actionable quality feedback
 * identifiers.
 */
std::vector<std::string> getAllActionableIdentifiers();

/**
 * @brief
 * Obtain all quality feature IDs from quality modules.
 *
 * @return
 * Vector of strings containing all quality feature IDs.
 */
std::vector<std::string> getAllQualityFeatureIDs();

/**
 * @brief
 * Obtain all speed feature groups from quality modules.
 *
 * @return
 * Vector of strings containing all speed feature groups.
 */
std::vector<std::string> getAllSpeedFeatureGroups();

/**
 * @brief
 * Updates the floating point precision mode used on 32-bit Linux
 * versions of NFIQ 2.
 *
 * @details
 * On 32-bit linux machines the floating point calculations are inconsistent
 * with other 32 bit or 64 bit operating systems. Executing a specific
 * assembly instruction fixes the issue and allows for score computation
 * to behave as expected. To learn more about this specific floating point
 * issue, please see the following website:
 * https://www.linuxtopia.org/online_books/an_introduction_to_gcc/gccintro_70.html
 *
 * @param mode
 * Floating point precision mode
 */
void setFPU(unsigned int mode);

/**
 * @brief
 * Obtain computed quality feature data from a fingerprint image.
 *
 * @param rawImage
 * Fingerprint image in raw format.
 *
 * @return
 * A vector if BaseFeature modules containing computed feature data.
 */
std::vector<std::shared_ptr<NFIQ2::QualityFeatures::BaseFeature>>
computeQualityFeatures(const NFIQ2::FingerprintImageData &rawImage);

/**
 * @brief
 * Obtain actionable quality feedback from a vector of features.
 *
 * @param features
 * A vector of BaseFeatures obtained from a raw fingerprint image.
 *
 * @return
 * A map of string, actionable quality feedback pairs.
 */
std::unordered_map<std::string, NFIQ2::ActionableQualityFeedback>
getActionableQualityFeedback(
    const std::vector<std::shared_ptr<NFIQ2::QualityFeatures::BaseFeature>>
	&features);

/**
 * @brief
 * Obtain actionable quality feedback from a fingerprint image.
 *
 * @param rawImage
 * Fingerprint image in raw format.
 *
 * @return
 * A map of string, actionable quality feedback pairs.
 */
std::unordered_map<std::string, NFIQ2::ActionableQualityFeedback>
getActionableQualityFeedback(const NFIQ2::FingerprintImageData &rawImage);

/**
 * @brief
 * Obtain quality feature data from a vector of features.
 *
 * @param features
 * A vector of BaseFeatures obtained from a raw fingerprint image.
 *
 * @return
 * A map of string, quality feature data pairs.
 */
std::unordered_map<std::string, double> getQualityFeatureData(
    const std::vector<std::shared_ptr<NFIQ2::QualityFeatures::BaseFeature>>
	&features);

/**
 * @brief
 * Obtain quality feature data from a fingerprint image.
 *
 * @param rawImage
 * Fingerprint image in raw format.
 *
 * @return
 * A map of string, quality feature data pairs.
 */
std::unordered_map<std::string, double> getQualityFeatureData(
    const NFIQ2::FingerprintImageData &rawImage);

/**
 * @brief
 * Obtain quality feature speeds from a vector of features.
 *
 * @param features
 * A vector of BaseFeatures obtained from a raw fingerprint image.
 *
 * @return
 * A map of string, quality feature speed pairs.
 */
std::unordered_map<std::string, NFIQ2::QualityFeatureSpeed>
getQualityFeatureSpeeds(
    const std::vector<std::shared_ptr<NFIQ2::QualityFeatures::BaseFeature>>
	&features);

}}}

#endif /* NFIQ2_QUALITYFEATURES_IMPL_HPP_ */
