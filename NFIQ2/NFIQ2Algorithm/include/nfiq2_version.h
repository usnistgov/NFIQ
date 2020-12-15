#ifndef NFIQ2_VERSION_H_
#define NFIQ2_VERSION_H_

namespace NFIQ
{
  namespace Version
  {
    extern const unsigned int Major;
    extern const unsigned int Minor;
    extern const unsigned int Patch;

    extern const std::string Full;
    extern const std::string Pretty;
    extern const std::string Status;
    extern const std::string BuildDate;
    extern const std::string Commit;

    /*
     * Third-Party Components
     */

    std::string BiometricEvaluation();
    extern const std::string OpenCV;
    std::string FingerJet();
  }
}

#endif /* NFIQ2_VERSION_H_ */
