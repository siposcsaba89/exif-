#include "exifpp.h"
#include <map>

namespace exifpp
{

Exif::Exif()
{
}

Exif::~Exif()
{
}

void Exif::parse(std::iostream & exif_stream, std::streampos header_poss)
{
    
    std::streampos current_pos = exif_stream.tellg();
    std::streampos header_pos = header_poss;
    if ( header_pos == 0)
    {
        std::string exif_string("Exif00");
        exif_stream.read(&exif_string[0], 6);
        std::cout << exif_string << std::endl;

        char tiff_header[8];
        header_pos = exif_stream.tellg();

        exif_stream.read(tiff_header, sizeof(tiff_header));
        uint16_t * byte_order;
        byte_order = (uint16_t*)(tiff_header);
        std::cout << std::hex << *byte_order << std::endl;
        if (*byte_order == BYTE_ORDER_LITTLE_ENDIAN)
        {
            printf("little endian\n");
            m_byte_order = BYTE_ORDER_LITTLE_ENDIAN;
        }
        else if (*byte_order == BYTE_ORDER_BIG_ENDIAN)
        {
            m_byte_order = BYTE_ORDER_BIG_ENDIAN;

        }
        //42 not necessary, maybe can be skipped
        uint16_t * num_42 = (uint16_t*)(tiff_header + 2);
        printf("42 = %d \n", *num_42);
        uint32_t * offset = (uint32_t*)(tiff_header + 4);
        printf("offset = %d \n", *offset);
        //go to offset
        exif_stream.seekg(header_pos + std::streampos(*offset));
    }

    ///first ifd data reading
    uint16_t num_entries;
    exif_stream.read((char*)&num_entries, sizeof(num_entries));
    printf("num entries in the IFD (Image file directory) = %d \n", num_entries);
    m_entries.resize(num_entries);
    //read entries
    for (size_t i = 0; i < num_entries; ++i)
    {
        m_entries[i].read(exif_stream);
        //m_entries[i].print();
    }

    uint32_t next_ifd_offset;
    exif_stream.read((char*)&next_ifd_offset, sizeof(next_ifd_offset));
    printf("next ifd offset: %d \n", next_ifd_offset);

    //read ifd datas
    for (auto & entry : m_entries)
    {
        size_t data_size = entry.num_of_components * sizeOfComponents(entry.data_format);
        if (data_size > 4)
        {
            exif_stream.seekg(header_pos + std::streampos(entry.data_or_offest));
            if (entry.data_format == 2 || entry.data_format == 7) // text
            {
                entry.d_text.resize(entry.num_of_components);
                exif_stream.read(&entry.d_text[0], entry.num_of_components);
                printf("%s \n", entry.d_text.c_str());
            }
            else if (entry.data_format == 1) //byte
            {
                entry.d_bytes.resize(entry.num_of_components);
                exif_stream.read((char*)entry.d_bytes.data(), entry.num_of_components);
            }
            else if (entry.data_format == 3) //shorts
            {
                entry.d_shorts.resize(entry.num_of_components);
                exif_stream.read((char*)entry.d_shorts.data(), entry.num_of_components);
            }
            else if (entry.data_format == 4) //uint
            {
                entry.d_longs.resize(entry.num_of_components);
                exif_stream.read((char*)entry.d_longs.data(), entry.num_of_components);
            }
            else if (entry.data_format == 5) //urational
            {
                entry.d_urationals.resize(entry.num_of_components);
                exif_stream.read((char*)entry.d_urationals.data(), 
                                 data_size);
            }
            else if (entry.data_format == 9) //int
            {
                entry.d_slongs.resize(entry.num_of_components);
                exif_stream.read((char*)entry.d_slongs.data(), entry.num_of_components);
            }
            else if (entry.data_format == 10) //srational
            {
                entry.d_srationals.resize(entry.num_of_components);
                exif_stream.read((char*)entry.d_srationals.data(), data_size);
            }
        }
        entry.print();
        if (entry.entry_id == EXIF_FIELD_ExifIFDPointer)
        {
            exif_stream.seekg(header_pos + std::streampos(entry.data_or_offest));
            Exif e;
            e.parse(exif_stream, header_pos);
        }
        else if (entry.entry_id == EXIF_FIELD_GPSInfoIFDPointer)
        {
            exif_stream.seekg(header_pos + std::streampos(entry.data_or_offest));
            Exif e;
            e.parse(exif_stream, header_pos);
        }

    }

}

static const std::map<ExifFieldIDs, std::string> field_string_map =
{
    {EXIF_FIELD_ImageWidth, "ImageWidth"},
    {EXIF_FIELD_ImageLength, "ImageLength"},
    {EXIF_FIELD_BitsPerSample, "BitsPerSample"},
    {EXIF_FIELD_Compression, "Compression"},
    {EXIF_FIELD_PhotometricInterpretation, "PhotometricInterpretation"},
    {EXIF_FIELD_Orientation, "Orientation"},
    {EXIF_FIELD_SamplesPerPixel, "SamplesPerPixel"},
    {EXIF_FIELD_PlanarConfiguration, "PlanarConfiguration"},
    {EXIF_FIELD_YCbCrSubSampling, "YCbCrSubSampling"},
    {EXIF_FIELD_YCbCrPositioning, "YCbCrPositioning"},
    {EXIF_FIELD_XResolution, "XResolution"},
    {EXIF_FIELD_YResolution, "YResolution"},
    {EXIF_FIELD_ResolutionUnit, "ResolutionUnit"},
    {EXIF_FIELD_StripOffsets, "StripOffsets"},
    {EXIF_FIELD_RowsPerStrip, "RowsPerStrip"},
    {EXIF_FIELD_StripByteCounts, "StripByteCounts"},
    {EXIF_FIELD_JPEGInterchangeFormat, "JPEGInterchangeFormat"},
    {EXIF_FIELD_JPEGInterchangeFormatLength, "JPEGInterchangeFormatLength"},
    {EXIF_FIELD_TransferFunction, "TransferFunction"},
    {EXIF_FIELD_WhitePoint, "WhitePoint"},
    {EXIF_FIELD_PrimaryChromaticities, "PrimaryChromaticities"},
    {EXIF_FIELD_YCbCrCoefficients, "YCbCrCoefficients"},
    {EXIF_FIELD_ReferenceBlackWhite, "ReferenceBlackWhite"},
    {EXIF_FIELD_DateTime, "DateTime"},
    {EXIF_FIELD_ImageDescription, "ImageDescription"},
    {EXIF_FIELD_Make, "Make"},
    {EXIF_FIELD_Model, "Model"},
    {EXIF_FIELD_Software, "Software"},
    {EXIF_FIELD_Artist, "Artist"},
    {EXIF_FIELD_Copyright, "Copyright"},
    {EXIF_FIELD_ExifIFDPointer, "ExifIFDPointer"},
    {EXIF_FIELD_GPSInfoIFDPointer, "GPSInfoIFDPointer"},
    {EXIF_FIELD_ExifVersion, "ExifVersion"},
    {EXIF_FIELD_FlashpixVersion, "FlashpixVersion"},
    {EXIF_FIELD_ColorSpace, "ColorSpace"},
    {EXIF_FIELD_ComponentsConfiguration, "ComponentsConfiguration"},
    {EXIF_FIELD_CompressedBitsPerPixel, "CompressedBitsPerPixel"},
    {EXIF_FIELD_PixelXDimension, "PixelXDimension"},
    {EXIF_FIELD_PixelYDimension, "PixelYDimension"},
    {EXIF_FIELD_MakerNote, "MakerNote"},
    {EXIF_FIELD_UserComment, "UserComment"},
    {EXIF_FIELD_RelatedSoundFile, "RelatedSoundFile"},
    {EXIF_FIELD_DateTimeOriginal, "DateTimeOriginal"},
    {EXIF_FIELD_DateTimeDigitized, "DateTimeDigitized"},
    {EXIF_FIELD_SubSecTime, "SubSecTime"},
    {EXIF_FIELD_SubSecTimeOriginal, "SubSecTimeOriginal"},
    {EXIF_FIELD_SubSecTimeDigitized, "SubSecTimeDigitized"},
    {EXIF_FIELD_ImageUniqueID, "ImageUniqueID"},
    {EXIF_FIELD_ExposureTime, "ExposureTime"},
    {EXIF_FIELD_FNumber, "FNumber"},
    {EXIF_FIELD_ExposureProgram, "ExposureProgram"},
    {EXIF_FIELD_SpectralSensitivity, "SpectralSensitivity"},
    {EXIF_FIELD_ISOSpeedRatings, "ISOSpeedRatings"},
    {EXIF_FIELD_OECF, "OECF"},
    {EXIF_FIELD_ShutterSpeedValue, "ShutterSpeedValue"},
    {EXIF_FIELD_ApertureValue, "ApertureValue"},
    {EXIF_FIELD_BrightnessValue, "BrightnessValue"},
    {EXIF_FIELD_ExposureBiasValue, "ExposureBiasValue"},
    {EXIF_FIELD_MaxApertureValue, "MaxApertureValue"},
    {EXIF_FIELD_SubjectDistance, "SubjectDistance"},
    {EXIF_FIELD_MeteringMode, "MeteringMode"},
    {EXIF_FIELD_LightSource, "LightSource"},
    {EXIF_FIELD_Flash, "Flash"},
    {EXIF_FIELD_FocalLength, "FocalLength"},
    {EXIF_FIELD_SubjectArea, "SubjectArea"},
    {EXIF_FIELD_FlashEnergy, "FlashEnergy"},
    {EXIF_FIELD_SpatialFrequencyResponse, "SpatialFrequencyResponse"},
    {EXIF_FIELD_FocalPlaneXResolution, "FocalPlaneXResolution"},
    {EXIF_FIELD_FocalPlaneYResolution, "FocalPlaneYResolution"},
    {EXIF_FIELD_FocalPlaneResolutionUnit, "FocalPlaneResolutionUnit"},
    {EXIF_FIELD_SubjectLocation, "SubjectLocation"},
    {EXIF_FIELD_ExposureIndex, "ExposureIndex"},
    {EXIF_FIELD_SensingMethod, "SensingMethod"},
    {EXIF_FIELD_FileSource, "FileSource"},
    {EXIF_FIELD_SceneType, "SceneType"},
    {EXIF_FIELD_CFAPattern, "CFAPattern"},
    {EXIF_FIELD_CustomRendered, "CustomRendered"},
    {EXIF_FIELD_ExposureMode, "ExposureMode"},
    {EXIF_FIELD_WhiteBalance, "WhiteBalance"},
    {EXIF_FIELD_DigitalZoomRatio, "DigitalZoomRatio"},
    {EXIF_FIELD_FocalLengthIn35mmFilm, "FocalLengthIn35mmFilm"},
    {EXIF_FIELD_SceneCaptureType, "SceneCaptureType"},
    {EXIF_FIELD_GainControl, "GainControl"},
    {EXIF_FIELD_Contrast, "Contrast"},
    {EXIF_FIELD_Saturation, "Saturation"},
    {EXIF_FIELD_Sharpness, "Sharpness"},
    {EXIF_FIELD_DeviceSettingDescription, "DeviceSettingDescription"},
    {EXIF_FIELD_SubjectDistanceRange, "SubjectDistanceRange"},
    {EXIF_FIELD_SensitivityType, "SensitivityType"},
    {EXIF_FIELD_RecommendedExposureIndex, "RecommendedExposureIndex"},
    {EXIF_FIELD_InteroperabilityTag, "InteroperabilityTag"},
    {EXIF_FIELD_CameraOwnerName, "CameraOwnerName"},
    {EXIF_FIELD_BodySerialNumber, "BodySerialNumber"},
    {EXIF_FIELD_LensSpecification, "LensSpecification"},
    {EXIF_FIELD_LensModel, "LensModel"},
    {EXIF_FIELD_LensSerialNumber, "LensSerialNumber"}
};


std::string getFieldId(ExifFieldIDs field_id)
{
    auto it = field_string_map.find(field_id);
    if (it != field_string_map.end())
        return it->second;
    else
        return std::string("Unknown");
}

size_t sizeOfComponents(uint16_t data_format)
{
    switch (data_format)
    {
    case 1: case 2: case 7: return 1;
    case 3: return 2;
    case 4: case 9: return 4;
    case 5: case 10: return 8;
    default:
        return 0;
        break;
    }
}

}