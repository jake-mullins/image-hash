#include <iostream>
#include <noise/noise.h>
#include "noise/noiseutils.cpp"

template <typename T>
struct Generator
{
    T *gen = new T;
};

int main(int argc, char *argv[])
{
    int choice;
    std::cout << "Choice: " << std::endl;
    std::cin >> choice;

    noise::utils::NoiseMap heightMap;
    noise::utils::NoiseMapBuilderPlane heightMapBuilder;

    switch (choice)
    {
    // Initialize generator struct
    // Decide which kind of variable to use
    case 1:
    {
        Generator<noise::module::Perlin> *gen1 = new Generator<noise::module::Perlin>();
        std::cout << gen1->gen->GetValue(0.0, 0.3, 0.0) << std::endl;
        delete gen1;
    }
    case 2:
    {
        // Break this into a function
        noise::module::Perlin perlin;
        heightMapBuilder.SetSourceModule(perlin);
        heightMapBuilder.SetDestNoiseMap(heightMap);
        heightMapBuilder.SetDestSize(509, 512);
        heightMapBuilder.SetBounds(6.0, 10.0, 1.0, 5.0);
        heightMapBuilder.Build();
    }
    break;
    default:
    {
        std::cout << "You messed up bud" << std::endl;
        break;
    }
    }
    utils::RendererImage renderer;
    utils::Image image;
    renderer.SetSourceNoiseMap(heightMap);
    renderer.SetDestImage(image);
    renderer.ClearGradient();
    renderer.AddGradientPoint(-1.00, utils::Color(32, 160, 0, 255));   // grass
    renderer.AddGradientPoint(-0.25, utils::Color(224, 224, 0, 255));  // dirt
    renderer.AddGradientPoint(0.25, utils::Color(128, 128, 128, 255)); // rock
    renderer.AddGradientPoint(1.00, utils::Color(255, 255, 255, 255)); // snow
    renderer.EnableLight();
    renderer.SetLightContrast(3.0);
    renderer.SetLightBrightness(2.0);
    renderer.Render();

    utils::WriterBMP writer;
    writer.SetSourceImage(image);
    writer.SetDestFilename("tutorial.bmp");
    writer.WriteDestFile();
    return 0;
}