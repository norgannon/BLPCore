//
//  BLPCore.h
//  Blipper
//

#ifndef __Blipper__BLPCore__
#define __Blipper__BLPCore__

#include <iostream>
#include <vector>
#include <memory>
#include <iterator>
#include <squish/squish.h>

namespace BLPCore {
    typedef enum BLPCompressionType
    {
        BLPCompressionTypePalettized = 1,
        BLPCompressionTypeDXT = 2,
        BLPCompressionTypePlain = 3,
    } BLPCompressionType;
    
    typedef struct {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    } RGBAPixel;
    
    typedef struct {
        uint8_t b;
        uint8_t g;
        uint8_t r;
        uint8_t a;
    } BGRAPixel;
    
    typedef struct BLPHeader {
        char    magic[4];
        uint32_t   type;
        uint8_t    compressionType;
        uint8_t    alphaBits;
        uint8_t    alphaType;
        uint8_t    hasMips;
        uint32_t   width;
        uint32_t   height;
        uint32_t   mipmapOffsets[16];
        uint32_t   mipmapLengths[16];
        BGRAPixel  colorPalette[256];
    } BLPHeader;

    typedef std::vector<uint8_t> DataChunk;
    
    
    /*! @brief Returns the header of the given BLP file data.
     
     @param data	The data of 
    */
    BLPHeader GetBLPHeader(DataChunk data);
    bool CheckBLPMagic(DataChunk data);
    bool DecodeBLPData(DataChunk file, DataChunk &decodedFile);
    bool DecodeDXTBLP(DataChunk data, int width, int height, int alphaType, DataChunk &decodedData);
    bool DecodePalettizedBLP(DataChunk data, int width, int height, int alphaBits, BGRAPixel *palette, DataChunk &decodedData);
    DataChunk EncodePlainBLP(DataChunk pixels, int width, int height);
    DataChunk ARGBToRGBA(DataChunk ARGBData);
}

#endif /* defined(__Blipper__BLPCore__) */
