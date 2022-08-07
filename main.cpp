#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <fstream>
#include <sys/utsname.h>

std::string getOsName();

// Linux stuff (Developed on Ubuntu)
std::string getLinuxSpecificInputString();
utsname getUnameInfo();

int main(int argc, char *argv[])
{

    std::string inputString;
    std::string hostOS = getOsName();

    // Detect OS
    if (hostOS == "Linux")
    {
        std::cout << getLinuxSpecificInputString() << std::endl;
    }

    return 0;
}

std::string getOsName()
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
    std::string macStringContent(   (std::istreambuf_iterator<char>(ifs)),
                                    (std::istreambuf_iterator<char>()   ));
    total += macStringContent;

    return total;
}

#endif