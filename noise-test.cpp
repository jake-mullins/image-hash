#ifndef NOISE_TEST_CPP
#define NOISE_TEST_CPP

#include <fstream>
#include <iostream>
#include <noise/noise.h>

int main (int argc, char* argv[])
{

    noise::module::Perlin myModule;
    double value = myModule.GetValue (14.50, 20.25, 75.75);
    std::cout << value << std::endl;
    return 0;

//    // Make objects
//    noise::module::Perlin perlin1;
//    noise::utils::NoiseMap heightMap;
//    noise::utils::NoiseMapBuilderPlane heightMapBuilder;
//    
//    // Construct coherent noise
//    heightMapBuilder.SetSourceModule(perlin1);
//    heightMapBuilder.SetDestNoiseMap(heightMap);
//    heightMapBuilder.SetDestSize(256,256);
//    heightMapBuilder.SetBounds(2.0,6.0,1.0,5.0);
//    heightMapBuilder.Build();
//
//    // Render image
//    noise::utils::RendererImage renderer;
//    noise::utils::Image image;
//    renderer.SetSourceNoiseMap(heightMap);
//    renderer.SetDestImage(image);
//
//    renderer.Render();
//
//    return 0;
}

#endif