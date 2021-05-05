#ifndef NFIQ2_EXCEPTION_HPP_
#define NFIQ2_EXCEPTION_HPP_

#include <exception>
#include <map>
#include <string>

namespace NFIQ2 {

/** This enum class represents error codes defined within this framework. */
enum class ErrorCode {
	UnknownError,
	NotEnoughMemory,
	BadArguments,
	FeatureCalculationError,
	CannotWriteToFile,
	CannotReadFromFile,
	NoDataAvailable,
	CannotDecodeBase64,
	InvalidConfiguration,
	MachineLearningError,
	FJFX_CannotCreateContext,
	FJFX_CannotCreateFeatureSet,
	FJFX_NoFeatureSetCreated,
	InvalidNFIQ2Score,
	InvalidImageSize
};

/** Map of Error Codes and their respective error messages. */
static const std::map<NFIQ2::ErrorCode, std::string> errorCodeMessage {
	{ NFIQ2::ErrorCode::UnknownError, "Unknown error" },
	{ NFIQ2::ErrorCode::NotEnoughMemory, "Not enough memory" },
	{ NFIQ2::ErrorCode::BadArguments, "Bad arguments" },
	{ NFIQ2::ErrorCode::FeatureCalculationError,
	    "Feature calculation error" },
	{ NFIQ2::ErrorCode::CannotWriteToFile, "Cannot write to file" },
	{ NFIQ2::ErrorCode::CannotReadFromFile, "Cannot read from file" },
	{ NFIQ2::ErrorCode::NoDataAvailable, "No data available" },
	{ NFIQ2::ErrorCode::CannotDecodeBase64, "Cannot decode base64 string" },
	{ NFIQ2::ErrorCode::InvalidConfiguration,
	    "An invalid configuration entry was found" },
	{ NFIQ2::ErrorCode::MachineLearningError,
	    "An machine learning error occurred" },
	{ NFIQ2::ErrorCode::FJFX_CannotCreateContext,
	    "Cannot create context for FJFX feature extractor" },
	{ NFIQ2::ErrorCode::FJFX_CannotCreateFeatureSet,
	    "Cannot create feature set from fingerprint data" },
	{ NFIQ2::ErrorCode::FJFX_NoFeatureSetCreated,
	    "No feature set could be created" },
	{ NFIQ2::ErrorCode::InvalidNFIQ2Score, "Invalid NFIQ2 Score" },
	{ NFIQ2::ErrorCode::InvalidImageSize, "Invalid Image Size" }
};

/** Represents the exception class used within this framework. */
class Exception : public std::exception {
    public:
	/** Constructor which uses supplied error code and default message. */
	Exception(const NFIQ2::ErrorCode &errorCode);

	/**
	 * Constructor which uses supplied error code and user-defined message.
	 */
	Exception(
	    const NFIQ2::ErrorCode &errorCode, const std::string &errorMessage);

	/** Destructor. */
	virtual ~Exception() noexcept;

	/**
	 * @brief
	 * Inherited function from std::exception.
	 *
	 * @return
	 * The exception message.
	 */
	virtual const char *what() const noexcept;

	/**
	 * @brief
	 * Obtain the return code of the exception.
	 *
	 * @return
	 * The return code.
	 */
	NFIQ2::ErrorCode getErrorCode() const;

	/**
	 * @brief
	 * Returns the error message of the exception.
	 *
	 * @return
	 * The error message.
	 */
	std::string getErrorMessage() const;

    private:
	/** The return code of the exception. */
	NFIQ2::ErrorCode errorCode;
	/** The error message of the exception. */
	std::string errorMessage;
};
} // namespace NFIQ

#endif /* NFIQ2_EXCEPTION_HPP_ */
