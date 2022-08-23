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
    noise::module::Module* perlin = new noise::module::Perlin();
    noise::module::Module* abs = new noise::module::Abs();
    (*abs).SetSourceModule(perlin);

    return 0;
}