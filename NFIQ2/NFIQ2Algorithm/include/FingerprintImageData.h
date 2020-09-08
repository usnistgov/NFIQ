#ifndef FINGERPRINTIMAGEDATA_H
#define FINGERPRINTIMAGEDATA_H

#include "include/Data.h"

#if defined WIN32 || defined WINDOWS
#include <windows.h>
#else
typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
#endif

#define MU_THRESHOLD 250

#define c_BI_RGB 0

namespace NFIQ
{

#pragma pack(1)

  typedef struct BITMAPFILEHEADER_t
  {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
  } BITMAPFILEHEADER;

  typedef struct BITMAPINFOHEADER_t
  {
    DWORD biSize;
    DWORD biWidth;
    DWORD biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    DWORD biXPelsPerMeter;
    DWORD biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
  } BITMAPINFOHEADER;

  typedef struct RGBQUAD_t
  {
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    BYTE rgbReserved;
  } RGBQUAD;

#pragma pack()

  /**
  * This type represents the resolution of an image (in dpi)
  */
  typedef enum image_resolution_e
  {
    e_ImageResolution_500dpi = 500,   ///< 500 dpi
    e_ImageResolution_1000dpi = 1000  ///< 1000 dpi
  } ImageResolution;

  /**
  ******************************************************************************
  * @class FingerprintImageData
  * @brief This class manages fingerprint image data (derived from class Data).
  ******************************************************************************/
  class FingerprintImageData : public Data
  {
    public:

      /******************************************************************************/
      // --- Constructor / Destructor --- //
      /******************************************************************************/

      /**
      * @brief Default constructor of FingerprintImageData
      */
      FingerprintImageData();

      /**
      * @brief Constructor of FingerprintImageData
      */
      FingerprintImageData(
        uint32_t imageWidth,
        uint32_t imageHeight,
        uint8_t fingerCode,
        uint16_t imageDPI );

      /**
      * @brief Constructor of data with available pointer to data
      */
      FingerprintImageData(
        const uint8_t* pData,
        uint32_t dataSize,
        uint32_t imageWidth,
        uint32_t imageHeight,
        uint8_t fingerCode,
        uint16_t imageDPI );

      /**
      * @brief Copy constructor
      */
      FingerprintImageData( const FingerprintImageData& otherData );

      /**
      * @brief Destructor
      */
      virtual ~FingerprintImageData();

      /******************************************************************************/
      // --- Public Members --- //
      /******************************************************************************/

      uint32_t  m_ImageWidth; ///< Width of the fingerprint image (in pixels)
      uint32_t  m_ImageHeight;  ///< Height of the fingerprint image (in pixels)
      uint8_t   m_FingerCode; ///< ISO finger code of the fingerprint in the image
      int16_t   m_ImageDPI; ///< Dots per inch of the fingerprint image (default: 500 dpi)

      /******************************************************************************/
      // --- Image Format Conversion Functions --- //
      /******************************************************************************/

      /**
      * @fn removeWhiteFrameAroundFingerprint
      * @brief Uses a simple algorithm to remove white lines around the fingerprint image (internally represented in raw data format).
      * @return The cropped/segmented fingerprint image in raw format.
      * @throws NFIQException
      */
      NFIQ::FingerprintImageData removeWhiteFrameAroundFingerprint();

  };
}

#endif

/******************************************************************************/
