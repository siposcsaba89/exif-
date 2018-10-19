#pragma once
#include <inttypes.h>
#include <string>
#include <iostream>
#include <vector>

namespace exifpp
{

enum MarkerCode : uint8_t
{
    MARKER_CODE_IMAGE_START = 0xD8,
    MARKER_CODE_FRAME_START = 0xC0,
    MARKER_CODE_APP_SPECIFIC_0 = 0xE0,
    MARKER_CODE_APP_SPECIFIC_1_EXIF = 0xE1,
    MARKER_CODE_APP_SPECIFIC_2 = 0xE2,
    MARKER_CODE_APP_SPECIFIC_3 = 0xE3,
    MARKER_CODE_APP_SPECIFIC_4 = 0xE4,
    MARKER_CODE_APP_SPECIFIC_5 = 0xE5,
    MARKER_CODE_APP_SPECIFIC_6 = 0xE6,
    MARKER_CODE_APP_SPECIFIC_7 = 0xE7,
    MARKER_CODE_OTHER
};

enum EntryDataType : uint16_t
{
    ENTRY_DATA_TYPE_BYTE = 1,
    ENTRY_DATA_TYPE_STRING = 2,
    ENTRY_DATA_TYPE_SHORT = 3,
    ENTRY_DATA_TYPE_LONG = 4,
    ENTRY_DATA_TYPE_RATIONAL = 5,
    ENTRY_DATA_TYPE_UNIDENTIFIED = 7,
    ENTRY_DATA_TYPE_SLONG = 9,
    ENTRY_DATA_TYPE_SRATIONAL = 10
};


enum ExifFieldIDs : uint16_t
{
    EXIF_FIELD_ImageWidth  = 0x100,
    EXIF_FIELD_ImageLength  = 0x101,
    EXIF_FIELD_BitsPerSample  = 0x102,
    EXIF_FIELD_Compression  = 0x103,
    EXIF_FIELD_PhotometricInterpretation  = 0x106,
    EXIF_FIELD_Orientation  = 0x112,
    EXIF_FIELD_SamplesPerPixel  = 0x115,
    EXIF_FIELD_PlanarConfiguration = 0x11C,
    EXIF_FIELD_YCbCrSubSampling  = 0x212,
    EXIF_FIELD_YCbCrPositioning  = 0x213,
    EXIF_FIELD_XResolution = 0x11A,
    EXIF_FIELD_YResolution = 0x11B,
    EXIF_FIELD_ResolutionUnit = 0x128,
    EXIF_FIELD_StripOffsets  = 0x111,
    EXIF_FIELD_RowsPerStrip  = 0x116,
    EXIF_FIELD_StripByteCounts  = 0x117,
    EXIF_FIELD_JPEGInterchangeFormat  = 0x201,
    EXIF_FIELD_JPEGInterchangeFormatLength  = 0x202,
    EXIF_FIELD_TransferFunction  = 0x12D,
    EXIF_FIELD_WhitePoint  = 0x13E,
    EXIF_FIELD_PrimaryChromaticities  = 0x13F,
    EXIF_FIELD_YCbCrCoefficients = 0x211,
    EXIF_FIELD_ReferenceBlackWhite = 0x214,
    EXIF_FIELD_DateTime = 0x132,
    EXIF_FIELD_ImageDescription = 0x10E,
    EXIF_FIELD_Make = 0x10F,
    EXIF_FIELD_Model = 0x110,
    EXIF_FIELD_Software = 0x131,
    EXIF_FIELD_Artist = 0x13B,
    EXIF_FIELD_Copyright = 0x8298,
    EXIF_FIELD_ExifIFDPointer = 0x8769,
    EXIF_FIELD_GPSInfoIFDPointer = 0x8825,
    EXIF_FIELD_ExifVersion = 0x9000,
    EXIF_FIELD_FlashpixVersion = 0xA000,
    EXIF_FIELD_ColorSpace = 0xA001,
    EXIF_FIELD_ComponentsConfiguration = 0x9101,
    EXIF_FIELD_CompressedBitsPerPixel = 0x9102,
    EXIF_FIELD_PixelXDimension = 0xA002,
    EXIF_FIELD_PixelYDimension = 0xA003,
    EXIF_FIELD_MakerNote = 0x927C,
    EXIF_FIELD_UserComment = 0x9286,
    EXIF_FIELD_RelatedSoundFile = 0xA004,
    EXIF_FIELD_DateTimeOriginal = 0x9003,
    EXIF_FIELD_DateTimeDigitized = 0x9004,
    EXIF_FIELD_SubSecTime = 0x9290,
    EXIF_FIELD_SubSecTimeOriginal = 0x9291,
    EXIF_FIELD_SubSecTimeDigitized = 0x9292,
    EXIF_FIELD_ImageUniqueID = 0xA420,
    EXIF_FIELD_ExposureTime = 0x829A,
    EXIF_FIELD_FNumber = 0x829D,
    EXIF_FIELD_ExposureProgram = 0x8822,
    EXIF_FIELD_SpectralSensitivity = 0x8824,
    EXIF_FIELD_ISOSpeedRatings = 0x8827,
    EXIF_FIELD_OECF = 0x8828,
    EXIF_FIELD_ShutterSpeedValue = 0x9201,
    EXIF_FIELD_ApertureValue = 0x9202,
    EXIF_FIELD_BrightnessValue = 0x9203,
    EXIF_FIELD_ExposureBiasValue = 0x9204,
    EXIF_FIELD_MaxApertureValue = 0x9205,
    EXIF_FIELD_SubjectDistance = 0x9206,
    EXIF_FIELD_MeteringMode = 0x9207,
    EXIF_FIELD_LightSource = 0x9208,
    EXIF_FIELD_Flash = 0x9209,
    EXIF_FIELD_FocalLength = 0x920A,
    EXIF_FIELD_SubjectArea = 0x9214,
    EXIF_FIELD_FlashEnergy = 0xA20B,
    EXIF_FIELD_SpatialFrequencyResponse = 0xA20C,
    EXIF_FIELD_FocalPlaneXResolution = 0xA20E,
    EXIF_FIELD_FocalPlaneYResolution = 0xA20F,
    EXIF_FIELD_FocalPlaneResolutionUnit = 0xA210,
    EXIF_FIELD_SubjectLocation = 0xA214,
    EXIF_FIELD_ExposureIndex = 0xA215,
    EXIF_FIELD_SensingMethod = 0xA215,
    EXIF_FIELD_FileSource = 0xA215,
    EXIF_FIELD_SceneType = 0xA215,
    EXIF_FIELD_CFAPattern = 0xA302,
    EXIF_FIELD_CustomRendered = 0xA401,
    EXIF_FIELD_ExposureMode = 0xA402,
    EXIF_FIELD_WhiteBalance = 0xA403,
    EXIF_FIELD_DigitalZoomRatio = 0xA404,
    EXIF_FIELD_FocalLengthIn35mmFilm = 0xA405,
    EXIF_FIELD_SceneCaptureType = 0xA406,
    EXIF_FIELD_GainControl = 0xA407,
    EXIF_FIELD_Contrast = 0xA408,
    EXIF_FIELD_Saturation = 0xA409,
    EXIF_FIELD_Sharpness = 0xA40A,
    EXIF_FIELD_DeviceSettingDescription = 0xA40B,
    EXIF_FIELD_SubjectDistanceRange = 0xA40C,
};


std::string getFieldId(ExifFieldIDs field_id);

struct JpegMarker
{
    uint8_t marker_code;
    std::string payload_data;
};

size_t sizeOfComponents(uint16_t data_format);

/*
12 byte - field interoperability array
    * 0-1 Tag - 2 byte number indentifies the field
    * 2-3 Type -
        - 1 - BYTE
        - 2 - An 8-bit byte containing one 7-bit ASCII code. The final byte is terminated with NULL.
        - 3 - SHORT 16 bit unsigned integer
        - 4 - LONG 32 bit unsigned integer
        - 5 - RATIONAL, 2 LONGs, first numerator, second denominator
        - 7 - UNDEFINED
        - 9 - SLONG 32 bit signed integer
        - 10- SRATIONAL 2 LONGs, first numerator, denominator
    * 4-7 Count - number of values, not the sum of bytes
    * 8-11 Value offset - This tag records the offset from the start of the TIFF header to the position where the value itself is recorded. In
           cases where the value fits in 4 bytes, the value itself is recorded. If the value is smaller than 4 bytes, the value is
           stored in the 4-byte area starting from the left, i.e., from the lower end of the byte offset area. For example, in big
           endian format, if the type is SHORT and the value is 1, it is recorded as 00010000.H.

*/
struct Entry
{
    uint16_t entry_id;
    uint16_t data_format;
    uint32_t num_of_components;
    uint32_t data_or_offest;

#pragma pack(4)
    struct urational
    {
        uint32_t numerator;
        uint32_t denominator;
    };

    struct srational
    {
        int32_t numerator;
        int32_t denominator;
    };
#pragma pack()
    union
    {
        std::string d_text;
        std::vector<uint8_t> d_bytes;
        std::vector<uint16_t> d_shorts;
        std::vector<uint32_t> d_longs;
        std::vector<int32_t> d_slongs;
        std::vector<urational> d_urationals;
        std::vector<srational> d_srationals;

    };

    void read(std::iostream & file)
    {
        char entry[12];
        file.read(entry, sizeof(entry));

        entry_id = *((uint16_t*)entry);
        data_format = *((uint16_t*)(entry + 2));
        num_of_components = *((uint32_t*)(entry + 4));
        data_or_offest = *((uint32_t*)(entry + 8));
    }

    void print()
    {
        printf("Entry id : %s \n \t data format: %d\n\t number of components: %d\n\t data_or_offset: %d \n",
               getFieldId((ExifFieldIDs)entry_id).c_str(), data_format, num_of_components, data_or_offest);
    }
    Entry() : d_text(){}
    Entry(const Entry & o) :d_text(o.d_text) {}
    ~Entry() {}
};


class Exif
{
public:
    Exif();
    ~Exif();
    void parse(std::iostream & exif_stream, std::streampos header_pos = std::streampos(0));
private:
    std::vector<Entry> m_entries;

    enum : uint16_t
    {
        BYTE_ORDER_LITTLE_ENDIAN = 0x4949,
        BYTE_ORDER_BIG_ENDIAN = 0x4D4D
    } m_byte_order;
};

}