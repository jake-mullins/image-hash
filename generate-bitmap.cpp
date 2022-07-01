#include <iostream>
#include <cstdint>

struct BmpHeader {
    char signatureBits[2] = {'B', 'M'};
    uint32_t sizeOfBitmapFile;
    uint32_t reservedBytes = 0;
    uint32_t startOfFileOffset = 54;

    BmpHeader(int width, int height) {
        this->sizeOfBitmapFile = startOfFileOffset + (width * height);
    }
};

struct BmpInfoHeader {
    uint32_t sizeOfInfoHeader = 40;
    int32_t width;
    int32_t height;
    uint16_t numOfColorPlanes = 1;
    uint16_t colorDepth = 24;
    uint32_t compressionValue = 0;      // 0 for no compression
    uint32_t imageSize = 0;             // Ignored
    uint32_t horizontalRes = 3780;
    uint32_t verticalRes = 3780;
    uint32_t numOfColors = 0;
    uint32_t numOfImportantColors = 0;  // Ignored
    BmpInfoHeader(int width, int height) {
        this->width = width;
        this->height = height;
    }
};

struct Pixel {
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    
    Pixel(uint8_t red, uint8_t green, uint8_t blue){
        this->red = red;
        this->green = green;
        this->blue = blue;
    }
};

int main(int argc, char *argv[]) {
//    std::ofstream fout("output.bmp", std::ios::binary);

//    fout.write((char *) &BmpHeader, 14);
//    fout.write((char *) &BmpInfoHeader, 40);

    // Writing pixel data
//    size_t numberOfPixels = 

    for (size_t i = 1; i < argc; i++){
        std::cout << argv[i];
    }

    return 0;
}

