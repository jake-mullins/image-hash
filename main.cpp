#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <fstream>
#include <vector>
#include <sys/utsname.h>

#include <noise/noise.h>
#include "noise/noiseutils.h"

std::string getOSName();

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
    if (args.at(0) == "--local") {
        std::cout << "Generating a bitmap (hopefully) unique to your computer..." << std::endl;
        generatePicture();
        return 0;
    }

    // Not enough args
    if (args.at(0) == "--input" && args.size() == 1) {
        printError("No input given");
        printFullHelp();
        return 0;
    }

    // Generate map using command line input
    if (args.at(0) == "--input" && args.size() == 2) {
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


// UI Stuff
void printError(std::string errorExplanation) {
    std::cout << "error: " << errorExplanation << std::endl << std::endl;
}
void printFullHelp() {
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
void generatePicture() {
    std::string OSName = getOSName();

    if (OSName == "Linux") {
        generateLinuxPicture();
    } else {
        printError("Unsupported OS. If you want this OS to be supported, contribute to this project!");
    }
}

void generateLinuxPicture() {
    std::string inputString = getLinuxSpecificInputString();
    std::cout << inputString << std::endl;

    noise::module::Perlin perlin;
    double value = perlin
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


#endif