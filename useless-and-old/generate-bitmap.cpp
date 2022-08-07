#include <iostream>
#include <fstream>
#include <cstdint>

struct BmpHeader {
    char signatureBits[2] = {'B', 'M'};
    uint32_t sizeOfBitmapFile;
    uint32_t reservedBytes = 0;
    uint32_t startOfFileOffset = 54;

    void save_to_file(std::ofstream& fout) {
        fout.write((char*)&this->signatureBits, 2);
        fout.write((char*)&this->sizeOfBitmapFile, sizeof(uint32_t));
        fout.write((char*)&this->reservedBytes, sizeof(uint32_t));
        fout.write((char*)&this->startOfFileOffset, sizeof(uint32_t));
    };

    BmpHeader() = default;
    BmpHeader(int width, int height) {
        this->sizeOfBitmapFile = startOfFileOffset + (width * height);
    };
} bmpHeader;

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

void save_on_file(std::ofstream& fout) {
    fout.write((char*)&this->sizeOfInfoHeader, sizeof(uint32_t));
    fout.write((char*)&this->width, sizeof(int32_t));
    fout.write((char*)&this->height, sizeof(int32_t));
    fout.write((char*)&this->numOfColorPlanes, sizeof(uint16_t));
    fout.write((char*)&this->colorDepth, sizeof(uint16_t));
    fout.write((char*)&this->compressionValue, sizeof(uint32_t));
    fout.write((char*)&this->imageSize, sizeof(uint32_t));
    fout.write((char*)&this->horizontalRes, sizeof(int32_t));
    fout.write((char*)&this->verticalRes, sizeof(int32_t));
    fout.write((char*)&this->numOfColors, sizeof(uint32_t));
    fout.write((char*)&this->numOfImportantColors, sizeof(uint32_t));
  }

    BmpInfoHeader() = default;
    BmpInfoHeader(int width, int height) {
        this->width = width;
        this->height = height;
    }
} bmpInfoHeader;

struct Pixel {
    uint8_t red = 255;
    uint8_t green = 255;
    uint8_t blue = 255;
    
    Pixel() = default;
    Pixel(uint8_t red, uint8_t green, uint8_t blue){
        this->red = red;
        this->green = green;
        this->blue = blue;
    }
} pixel;

int main(int argc, char *argv[]) {
    std::ofstream fout("output.bmp", std::ios::binary);

    struct BmpHeader testHeader(300,500);
    struct BmpInfoHeader testInfoHeader(300,500);

    fout.write((char *) &testHeader, 14);
    fout.write((char *) &testInfoHeader, 40);
    
    // Writing pixel data
    size_t numberOfPixels = bmpInfoHeader.width * bmpInfoHeader.height;
    for(int i = 0; i < numberOfPixels; i++) {
        fout.write((char *) &pixel, 3);
    } 
    fout.close();


    return 0;
}

