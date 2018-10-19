#include <iostream>
#include <string>
#include <fstream>
#include <inttypes.h>
#include <sstream>
#include "exifpp.h"


/*  Maximum two IFD, max 64 Kbytes, 
        APP1 marker -> 
        APP1 Length ->
        Exif identifier Code -> 
        TIFF Header ->
        0th IFD ->
        0th IFD Value ->
        1st IFD->
        1st IFD Value->
        1st IFD Image Data
    
     0 IFD records primary image information
     1 IFD records thumbnail image

     Tiff header 8 byte:
        * 2 - Byte order
             - "II" 0x4949 - little endian
             - "MM" 0x4D4D - big endian
        * 2 - fixed with value 0x002A (42)
        * 4 - 0th IFD offset. If tiff header followed immediately by the 0th IFD, it is written as 0x00000008

     IFD structure
     2 byte - number of field
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
     4 byte offset to the next IFD, in conformance with Tiff Rev. 6.0
*/
//assume that the file pointer point to a marker
exifpp::JpegMarker readMarker(std::ifstream & jpeg_stream)
{
    exifpp::JpegMarker ret;
    uint8_t t[2];
    jpeg_stream.read((char*)&t, sizeof(t));
    ret.marker_code = t[1];
    if (ret.marker_code < 0xD0 || ret.marker_code > 0xD9) //codes from 0xD0 to 0xD9 not have any data
    {
        uint16_t payload_length = 0;
        jpeg_stream.read((char*)&payload_length, sizeof(payload_length));
        if (payload_length > 2)
        {
            ret.payload_data.resize(payload_length - 2);
            jpeg_stream.read(&ret.payload_data[0], ret.payload_data.size());
        }
    }
    return ret;
}

int main()
{
    std::string jpeg_file = "g:/Pictures/2018_03_18/IMG_1561.JPG";
    
    std::ifstream file(jpeg_file, std::ios::binary);

    while (true)
    {
        if (file.is_open())
        {
            auto a = readMarker(file);
            if (a.marker_code == exifpp::MARKER_CODE_APP_SPECIFIC_1_EXIF)
            {
                std::stringstream ss(a.payload_data);
                exifpp::Exif exif;
                exif.parse(ss);

            }
        }
    }

    file.close();

    return 0;
}