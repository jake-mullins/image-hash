#ifndef SAMPLE_CPP
#define SAMPLE_CPP

#include <fstream>
#include <iostream>
#include <noise/noise.h>
#include "noiseutils.cpp"

int main(int argc, char **argv)
{
    noise::module::Perlin myModule;

    // Perlin noise configuration
    myModule.SetOctaveCount(6);
    myModule.SetFrequency(1.0);
    myModule.SetPersistence(0.5);

    // Build options
    noise::utils::NoiseMap heightMap;
    noise::utils::NoiseMapBuilderPlane heightMapBuilder;
    heightMapBuilder.SetSourceModule(myModule);
    heightMapBuilder.SetDestNoiseMap(heightMap);
    heightMapBuilder.SetDestSize(256, 256);
    heightMapBuilder.SetBounds(6.0, 10.0, 1.0, 5.0);
    heightMapBuilder.Build();

    // Renderer configration
    noise::utils::RendererImage renderer;
    noise::utils::Image image;
    renderer.SetSourceNoiseMap(heightMap);
    renderer.SetDestImage(image);
    renderer.ClearGradient();
    renderer.AddGradientPoint(-1.0000, utils::Color(0, 0, 128, 255));    // deeps
    renderer.AddGradientPoint(-0.2500, utils::Color(0, 0, 255, 255));    // shallow
    renderer.AddGradientPoint(0.0000, utils::Color(0, 128, 255, 255));   // shore
    renderer.AddGradientPoint(0.0625, utils::Color(240, 240, 64, 255));  // sand
    renderer.AddGradientPoint(0.1250, utils::Color(32, 160, 0, 255));    // grass
    renderer.AddGradientPoint(0.3750, utils::Color(224, 224, 0, 255));   // dirt
    renderer.AddGradientPoint(0.7500, utils::Color(128, 128, 128, 255)); // rock
    renderer.AddGradientPoint(1.0000, utils::Color(255, 255, 255, 255)); // snow
    renderer.EnableLight();
    renderer.SetLightContrast(3.0);   // Triple the contrast
    renderer.SetLightBrightness(2.0); // Double the brightness
    renderer.Render();

    // File writer
    noise::utils::WriterBMP writer;
    writer.SetSourceImage(image);
    writer.SetDestFilename("tutorial.bmp");
    writer.WriteDestFile();

    return 0;
}

#endif