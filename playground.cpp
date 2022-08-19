#include <iostream>

#include <noise/noise.h>
#include "noise/noiseutils.cpp"

noise::module::Module* getGenerator(int choice) {
    switch(choice) {
        case(1):
            return new noise::module::Perlin();
        case(2):
            return new noise::module::Const();
        default:
            return new noise::module::Voronoi();
    }
}

int main(int argc, char** argv) {
    noise::module::Perlin perlin;

    noise::module::Module* gen1 = new noise::module::Perlin();
    std::cout << gen1->GetValue(0.1,0.1,0.1) << std::endl;

    noise::module::Module* gen2 = getGenerator(1);
    std::cout << gen2->GetValue(0.5,0.5,0.5) << std::endl;

    noise::module::Module* gen3 = getGenerator(2);
    std::cout << gen3->GetValue(0.5,0.5,0.5) << std::endl;

    noise::module::Module* gen4 = getGenerator(3);
    std::cout << gen4->GetValue(0.5,0.5,0.5) << std::endl;
}