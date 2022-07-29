#ifndef NOISE_TEST_CPP
#define NOISE_TEST_CPP

#include <iostream>
#include <noise/noise.h>

using namespace noise;

int main (int argc, char** argv)
{
    module::Perlin myModule;
    double value = myModule.GetValue (1.25, 0.75, 0.50);
    std::cout << value << std::endl;
    return 0;
}

#endif