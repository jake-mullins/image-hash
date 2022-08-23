#include <iostream>

int main(int argc, char* argv[]) {
    srand(0);

    const int lowEndGradient = -1;
    const int highEndGradient = 1;

    float highest = -1;
    float lowest = 1;
    for(int i = 0; i < 100000; ++i) {
        float curr = lowEndGradient + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(highEndGradient-lowEndGradient)));
        if(curr > highest) {
            highest = curr;
        }
        if(curr < lowest) { 
            lowest = curr;
        }
    }

    std::cout << "Highest " << highest << std::endl;
    std::cout << "Lowest " << lowest << std::endl;
}