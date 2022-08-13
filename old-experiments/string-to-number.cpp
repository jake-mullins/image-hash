#include <iostream>
#include <bitset>
#include <string>
#include <cmath>

// This works because it leverages what cpus are best at
int main(int argc, char* argv[]) 
{
    std::string inputString = argv[1];
    unsigned int runningTotal = 0;

    for(int i = 0; i < inputString.length(); ++i) {
        runningTotal += i * pow(2,8) + inputString[i];
    }

    std::cout << runningTotal << std::endl;

    return 0;
}