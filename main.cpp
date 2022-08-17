#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <sys/utsname.h>

#include <noise/noise.h>
#include "noise/noiseutils.h"

// Utils
std::string getOSName();
unsigned int intRepresentationOfString(std::string input);

// Linux stuff (Developed on Ubuntu)
std::string getLinuxSpecificInputString();
utsname getUnameInfo();

// UI stuff
std::string fullHelpPath = "ui-text/help-page";
void printFullHelp();
void printError(std::string errorExplanation);

// Generator stuff
std::string outputPath = "output.bmp";
void generatePicture();
void generateLinuxPicture();
void generatePictureBySeed(std::string seed);

// High adjacent primes can be used for easy predictable decision making
// Source: https://youtu.be/GjkjJwPUgsA

int main(int argc, char **argv)
{
    std::vector<std::string> args;
    for (int i = 1; i < argc; i++)
    {
        args.push_back(argv[i]);
    }

    // Help menu
    if (args.empty() || args.at(0) == "--help")
    {
        printFullHelp();
        return 0;
    }

    // Generate map using hardware information
    if (args.at(0) == "--local")
    {
        std::cout << "Generating a bitmap (hopefully) unique to your computer..." << std::endl;
        generatePicture();
        return 0;
    }

    // Not enough args
    if (args.at(0) == "--input" && args.size() == 1)
    {
        printError("No input given");
        printFullHelp();
        return 0;
    }

    // Generate map using command line input
    if (args.at(0) == "--input" && args.size() == 2)
    {
        return 0;
    }

    return 0;
}

std::string getOSName()
{
#ifdef _WIN32
    return "Windows 32-bit";
#elif _WIN64
    return "Windows 64-bit";
#elif __APPLE__ || __MACH__
    return "Mac OSX";
#elif __linux__
    return "Linux";
#elif __FreeBSD__
    return "FreeBSD";
#elif __unix || __unix__
    return "Unix";
#else
    return "Other";
#endif
}

unsigned int intRepresentationOfString(std::string input)
{

    unsigned int runningTotal = 0;

    for (int i = input.length(); i >= 0; --i)
    {
        runningTotal += i * pow(2, 8) + input[i];
    }

    return runningTotal;
}

// UI Stuff
void printError(std::string errorExplanation)
{
    std::cout << "error: " << errorExplanation << std::endl
              << std::endl;
}
void printFullHelp()
{
    // https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
    std::ifstream t;
    t.open(fullHelpPath);
    std::string line;
    while (t)
    {
        std::getline(t, line);
        std::cout << line << std::endl;
    }
    t.close();
}

// Generator
// Wrapper function
// Logic for deciding which OS to use
void generatePicture()
{
    std::string OSName = getOSName();

    if (OSName == "Linux")
    {
        generateLinuxPicture();
    }
    else
    {
        printError("Unsupported OS. If you want this OS to be supported, contribute to this project!");
    }
}

void generateLinuxPicture()
{
    std::string inputString = getLinuxSpecificInputString();
    generatePictureBySeed(inputString);
}

std::string getLinuxSpecificInputString()
{
    std::string total = "";

    // C(?) code pulled from https://stackoverflow.com/questions/3596310/c-how-to-use-the-function-uname
    // Gets, System name, Hostname, Distro release/version (how are they different?), Architecture, Domain name
    // On my ubuntu 22.04 running on WSL2 I get:
    /*
        system name = Linux
        node name   = Vulkan
        release     = 5.10.16.3-microsoft-standard-WSL2
        version     = #1 SMP Fri Apr 2 22:23:49 UTC 2021
        machine     = x86_64
        domain name = localdomain
    */

    struct utsname sysInfo;

    errno = 0;
    if (uname(&sysInfo) < 0)
    {
        // perror("uname");
        exit(EXIT_FAILURE);
    }
    // TODO Truly random number generator randomizing the order of the entries

    total += sysInfo.sysname;
    total += sysInfo.version;
    total += sysInfo.release;
    total += sysInfo.domainname;
    total += sysInfo.machine;
    total += sysInfo.nodename;

    // Getting a single MAC Address assuming there is on called eth0
    // TODO get ALL Macs in /sys/class/net dir
    std::string macString = "/sys/class/net/eth0/address";
    std::ifstream ifs(macString);

    // Based on a a prior input from that super snazzy immutable hardware information, decide whether or not to capitalize the MAC address
    // Could combine all of the sysInfo information together (hashing I guess?) and look at the last or a random bit to see if it is 1 or 0, adding a whole 'nother bit of complexity. Would have to make sure that the last entry is not the deciding factor
    std::string macStringContent((std::istreambuf_iterator<char>(ifs)),
                                 (std::istreambuf_iterator<char>()));
    total += macStringContent;

    return total;
}

void generatePictureBySeed(std::string seed)
{

    unsigned int intOfString = intRepresentationOfString(seed);

    // Don't need a hash, since this is open source, it wouldn't make the space of possible results larger
    // Could add computational complexity of done right. Some way that utilized difficult mathematical operations
    // Like cosine, factoring, exponential, not just add/multiplying + subtract/division
    // Square root?

    // Use input strng as seed for random number generator
    std::srand(intOfString);

    // For each decision, assign a decision value
    // Mod it by how many choices there are, assign the choice based on the result
    /*
        Generator
            9 type choices
            All are necessary
            9 total
        Modifier
            6 type choices
                Curve/Terrace is more than just input->output
            1 for not present
            7 total
        Combiner
            4 type choices with only 2 inputs
            All are necessary
            4 total
        Transformer
            4 type choices
            1 for not present
            5 total
        */

    const int numberOfDecisionPoints = 4;

    const int generatorOptions = 9;
    const int modifierOptions = 7;
    const int transformerOptions = 5;
    const int combinerOptions = 4;


    std::vector<int> decisionValuesFull;
    std::vector<int> decisionValuesTruncated;

    for (int i = 0; i < numberOfDecisionPoints; ++i)
    {
        decisionValuesFull.push_back(rand());
        decisionValuesTruncated.push_back(decisionValuesFull.at(i));
    }
    
    // Round 1 gens
    for(int i = 0; i < 4; ++i) {
        int generatorType = rand() % generatorOptions;
    }

    // Round 1 mods/transform
    for(int i = 0; i < 4; ++i) {
        int modOrTransformType = rand() % (modifierOptions + transformerOptions);
    }
    // Combiner 4 -> 2
    for(int i = 0; i < 4; ++i) {
        int combinerType = rand() % combinerOptions;
    }
    // Round 2 mods/transform
    for(int i = 0; i < 4; ++i) {
        int modOrTransformType = rand() % (modifierOptions + transformerOptions);
    }
    // Combiner 2 -> 1
    int generatorType = rand() % generatorOptions;

    // Round 3 mods/transforms
    int modOrTransformType = rand() % (modifierOptions + transformerOptions);

}

#endif