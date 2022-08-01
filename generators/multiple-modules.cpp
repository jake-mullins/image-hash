#ifndef MULTIPLE_MODULES_CPP
#define MULTIPLE_MODULES_CPP

#include <iostream>

#include <noise/noise.h>
#include "noiseutils.cpp"

int main(int argc, char *argv[])
{
    // Initialize and configure modules
    // Mountains
    noise::module::RidgedMulti mountainTerrain;

    // Base flat
    noise::module::Billow baseFlatTerrain;
    baseFlatTerrain.SetFrequency(2.0);

    // Feature flat
    noise::module::ScaleBias flatTerrain;
    flatTerrain.SetSourceModule(0, baseFlatTerrain);
    flatTerrain.SetScale(0.125);
    flatTerrain.SetBias(-0.75);

    // Creates a GIANT perlin noise function for biome boundaries
    noise::module::Perlin terrainType;
    terrainType.SetFrequency(0.5);
    terrainType.SetPersistence(0.25);

    // Assigns terrain to the map based on the boundaries from terrainType
    noise::module::Select terrainSelector;
    terrainSelector.SetSourceModule(0, flatTerrain);
    terrainSelector.SetSourceModule(1, mountainTerrain);
    terrainSelector.SetControlModule(terrainType);
    terrainSelector.SetBounds(0.0, 1000.0);
    terrainSelector.SetEdgeFalloff(0.125);

    // Adds
    noise::module::Turbulence finalTerrain;
    finalTerrain.SetSourceModule(0, terrainSelector);
    finalTerrain.SetFrequency(4.0);
    finalTerrain.SetPower(0.125);

    // Initialize and configure height map/Perlin noise generator
    noise::utils::NoiseMap heightMap;
    noise::utils::NoiseMapBuilderPlane heightMapBuilder;
    heightMapBuilder.SetSourceModule(finalTerrain);
    heightMapBuilder.SetDestNoiseMap(heightMap);
    heightMapBuilder.SetDestSize(512, 512);
    heightMapBuilder.SetBounds(6.0, 10.0, 1.0, 5.0);
    heightMapBuilder.Build();

    // Renderer initialization and configuration
    noise::utils::RendererImage renderer;
    noise::utils::Image image;
    renderer.SetSourceNoiseMap(heightMap);
    renderer.SetDestImage(image);

    // Color gradiant configuration
    renderer.ClearGradient();
    renderer.AddGradientPoint(-1.00, utils::Color(32, 160, 0, 255));   // grass
    renderer.AddGradientPoint(-0.25, utils::Color(224, 224, 0, 255));  // dirt
    renderer.AddGradientPoint(0.25, utils::Color(128, 128, 128, 255)); // rock
    renderer.AddGradientPoint(1.00, utils::Color(255, 255, 255, 255)); // snow
    renderer.EnableLight();
    renderer.SetLightContrast(3.0);
    renderer.SetLightBrightness(2.0);
    renderer.Render();

    // Bitmap configuration
    noise::utils::WriterBMP writer;
    writer.SetSourceImage(image);
    writer.SetDestFilename("Multiple.bmp");
    writer.WriteDestFile();

    return 0;
}

#endif