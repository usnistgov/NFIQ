#ifndef RANDOMFORESTML_H
#define RANDOMFORESTML_H

#include <nfiq2_interfacedefinitions.hpp>
#include <opencv2/ml.hpp>

#include <string>
#include <unordered_map>
#include <vector>

#undef EMBED_RANDOMFOREST_PARAMETERS

namespace NFIQ2 { namespace Prediction {

/**
 * @class RandomForestML
 * @brief This class handles the Random Forest Machine Learning model used
 * to generate NFIQ 2 quality scores.
 */
class RandomForestML {

    public:
	/**
	 * @brief Default constructor of RandomForestML
	 */
	RandomForestML();
	/**
	 * @brief Destructor
	 */
	virtual ~RandomForestML();

	/** Stores the module name of the random RandomForestML object */
	static const std::string moduleName;

	/**
	 * @brief Returns the Random Forest Module name
	 */
	std::string getModuleName() const;

#ifdef EMBED_RANDOMFOREST_PARAMETERS
	/**
	 * @brief Initialize model (When using embedded parameters)
	 */
	std::string initModule();
#endif

	/**
	 * @brief Initialize model (When not using embedded parameters)
	 */
	std::string initModule(
	    const std::string &fileName, const std::string &fileHash);

	/**
	 * @brief Compute NFIQ2 quality score based on model and provided
	 * QualityFeatureData
	 */
	void evaluate(
	    const std::unordered_map<std::string, NFIQ2::QualityFeatureData>
		&features,
	    const double &utilityValue, double &qualityValue,
	    double &deviation) const;

    private:
	/** OpenCV shared smart pointer refering to the RF model itself */
	cv::Ptr<cv::ml::RTrees> m_pTrainedRF;
	/** Calculates the hash of the RandomForest parameters */
	std::string calculateHashString(const std::string &s);
	/** Initialize model using string parameters */
	void initModule(const std::string &params);

#ifdef EMBED_RANDOMFOREST_PARAMETERS
	/** Extracts string parameters when model is embedded */
	std::string joinRFTrainedParamsString();
#endif
};

}}

#endif

/******************************************************************************/
