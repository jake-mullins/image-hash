#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <sys/utsname.h>

#include "libnoise/noise.h"

// Utils
std::string getOSName();
unsigned int intRepresentationOfString(std::string input);
double getRandomDoubleInRange(float lowerEnd, float upperEnd);

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
void generatePictureBySeed(std::string seed, std::string outputFileName);
void generatePictureByFile(std::string filePath);
void generatePictureByFile(std::string filePath, std::string outputFileName);

noise::module::Module *getGenerator(int choice);
noise::module::Module *getModifier(int choice);
noise::module::Module *getCombiner(int choice);

// High adjacent primes can be used for easy predictable decision making
// Source: https://youtu.be/GjkjJwPUgsA

int main(int argc, char **argv)
{
    std::cout << "hello" << std::endl;

    // Parse Args
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
        std::cout << "Generating a bitmap unique to your computer..." << std::endl;
        generatePicture();
        std::cout << "Done." << std::endl;
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
        std::cout << "Generating a bitmap using " << args.at(1) << " as input" << std::endl;
        generatePictureBySeed(args.at(1));
        std::cout << "Done." << std::endl;
        return 0;
    }

    // Generate map using command line input as custom output file name
    if (args.at(0) == "--input" && args.size() == 3)
    {
        std::cout << "Generating a bitmap called " << args.at(2) << " using " << args.at(1) << "as input" << std::endl;
        generatePictureBySeed(args.at(1), args.at(2));
        return 0;
    }

    // Generate map using file contents as seed
    if (args.at(0) == "--file" && args.size() == 1)
    {
        printError("No input file given");
        printFullHelp();
    }

    // Generate map using file contents as seed
    if (args.at(0) == "--file" && args.size() == 2)
    {
        std::cout << "Generating a bitmap using file " << args.at(1) << " as input" << std::endl;
        generatePictureByFile(args.at(1));
    }

    // Generate map using file contents as seed and output to a file
    if (args.at(0) == "--file" && args.size() == 3)
    {
        std::cout << "Generating a bitmap called " << args.at(2) << " using file " << args.at(1) << " as input" << std::endl;
        generatePictureByFile(args.at(1), args.at(2));
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

double getRandomDoubleInRange(float lowerEnd, float upperEnd)
{
    return lowerEnd + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (upperEnd - lowerEnd)));
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

    const noise::module::Module *gen1 = getGenerator(rand());
    noise::module::Module *mod1 = getModifier(rand());
    mod1->SetSourceModule(0, *(gen1));

    const noise::module::Module *gen2 = getGenerator(rand());
    noise::module::Module *mod2 = getModifier(rand());
    mod2->SetSourceModule(0, *(gen2));

    noise::module::Module *combiner1 = getCombiner(rand());
    combiner1->SetSourceModule(0, (*mod1));
    combiner1->SetSourceModule(1, (*mod2));

    const noise::module::Module *gen3 = getGenerator(rand());
    noise::module::Module *mod3 = getModifier(rand());
    mod3->SetSourceModule(0, *(gen3));

    const noise::module::Module *gen4 = getGenerator(rand());
    noise::module::Module *mod4 = getModifier(rand());
    mod4->SetSourceModule(0, *(gen4));

    noise::module::Module *combiner2 = getCombiner(rand());
    combiner2->SetSourceModule(0, (*mod3));
    combiner2->SetSourceModule(1, (*mod4));

    noise::module::Module *mod5 = getModifier(rand());
    mod5->SetSourceModule(0, *(combiner1));

    noise::module::Module *mod6 = getModifier(rand());
    mod6->SetSourceModule(0, *(combiner2));

    noise::module::Module *combiner3 = getCombiner(rand());
    combiner3->SetSourceModule(0, (*mod1));
    combiner3->SetSourceModule(1, (*mod2));

    // Break rendering into it's own function
    // void renderMap(noise::module::Module* module);

    noise::utils::NoiseMap heightMap;
    noise::utils::NoiseMapBuilderPlane heightMapBuilder;

    heightMapBuilder.SetSourceModule((*combiner3));
    heightMapBuilder.SetDestNoiseMap(heightMap);
    heightMapBuilder.SetDestSize(512, 512);
    heightMapBuilder.SetBounds(0.0, 5.0, 0.0, 5.0);
    heightMapBuilder.Build();

    noise::utils::RendererImage renderer;
    noise::utils::Image image;

    renderer.SetSourceNoiseMap(heightMap);
    renderer.SetDestImage(image);
    renderer.ClearGradient();
    renderer.EnableLight();

    renderer.AddGradientPoint(-1.00, noise::utils::Color(rand() % 256, rand() % 256, rand() % 256, 255));
    // For a random number of times (2-6)
    // Add a new gradient point
    for (int i = 0; i < (rand() % 5); ++i)
    {
        renderer.AddGradientPoint(getRandomDoubleInRange(-1.0, 1.0), noise::utils::Color(rand() % 256, rand() % 256, rand() % 256, 255));
    }

    renderer.AddGradientPoint(1.00, noise::utils::Color(rand() % 256, rand() % 256, rand() % 256, 255));

    renderer.SetLightContrast(3.0);
    renderer.SetLightBrightness(2.0);
    renderer.Render();

    noise::utils::WriterBMP writer;
    writer.SetSourceImage(image);
    writer.SetDestFilename("fingerprint.bmp");
    writer.WriteDestFile();

    // Round 1 mods/transform
    // Combiner 4 -> 2
    // Round 2 mods/transform
    // Combiner 2 -> 1
    // Round 3 mods/transforms

    // Memory management
}

void generatePictureBySeed(std::string seed, std::string outputFileName)
{
    unsigned int intOfString = intRepresentationOfString(seed);

    // Don't need a hash, since this is open source, it wouldn't make the space of possible results larger
    // Could add computational complexity of done right. Some way that utilized difficult mathematical operations
    // Like cosine, factoring, exponential, not just add/multiplying + subtract/division
    // Square root?

    // Use input strng as seed for random number generator
    std::srand(intOfString);
#ifdef DEBUG
    std::cout << rand() << std::endl;
#endif

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

    const noise::module::Module *gen1 = getGenerator(rand());
    noise::module::Module *mod1 = getModifier(rand());
    mod1->SetSourceModule(0, *(gen1));

    const noise::module::Module *gen2 = getGenerator(rand());
    noise::module::Module *mod2 = getModifier(rand());
    mod2->SetSourceModule(0, *(gen2));

    noise::module::Module *combiner1 = getCombiner(rand());
    combiner1->SetSourceModule(0, (*mod1));
    combiner1->SetSourceModule(1, (*mod2));

    const noise::module::Module *gen3 = getGenerator(rand());
    noise::module::Module *mod3 = getModifier(rand());
    mod3->SetSourceModule(0, *(gen3));

    const noise::module::Module *gen4 = getGenerator(rand());
    noise::module::Module *mod4 = getModifier(rand());
    mod4->SetSourceModule(0, *(gen4));

    noise::module::Module *combiner2 = getCombiner(rand());
    combiner2->SetSourceModule(0, (*mod3));
    combiner2->SetSourceModule(1, (*mod4));

    noise::module::Module *mod5 = getModifier(rand());
    mod5->SetSourceModule(0, *(combiner1));

    noise::module::Module *mod6 = getModifier(rand());
    mod6->SetSourceModule(0, *(combiner2));

    noise::module::Module *combiner3 = getCombiner(rand());
    combiner3->SetSourceModule(0, (*mod1));
    combiner3->SetSourceModule(1, (*mod2));

    // Break rendering into it's own function
    // void renderMap(noise::module::Module* module);

    noise::utils::NoiseMap heightMap;
    noise::utils::NoiseMapBuilderPlane heightMapBuilder;

    heightMapBuilder.SetSourceModule((*combiner3));
    heightMapBuilder.SetDestNoiseMap(heightMap);
    heightMapBuilder.SetDestSize(512, 512);
    heightMapBuilder.SetBounds(0.0, 5.0, 0.0, 5.0);
    heightMapBuilder.Build();

    noise::utils::RendererImage renderer;
    noise::utils::Image image;

    renderer.SetSourceNoiseMap(heightMap);
    renderer.SetDestImage(image);
    renderer.ClearGradient();
    renderer.EnableLight();

    renderer.AddGradientPoint(-1.00, noise::utils::Color(rand() % 256, rand() % 256, rand() % 256, 255));
    // For a random number of times (2-6)
    // Add a new gradient point
    for (int i = 0; i < (rand() % 5); ++i)
    {
        renderer.AddGradientPoint(getRandomDoubleInRange(-1.0, 1.0), noise::utils::Color(rand() % 256, rand() % 256, rand() % 256, 255));
    }

    renderer.AddGradientPoint(1.00, noise::utils::Color(rand() % 256, rand() % 256, rand() % 256, 255));

    renderer.SetLightContrast(3.0);
    renderer.SetLightBrightness(2.0);
    renderer.Render();

    noise::utils::WriterBMP writer;
    writer.SetSourceImage(image);
    writer.SetDestFilename(outputFileName + ".bmp");
    writer.WriteDestFile();

    // Round 1 mods/transform
    // Combiner 4 -> 2
    // Round 2 mods/transform
    // Combiner 2 -> 1
    // Round 3 mods/transforms

    // Memory management?
}

void generatePictureByFile(std::string filePath)
{
    std::ifstream f;
    f.open(filePath);
    std::string inputString;
    while (f)
    {
        std::getline(f, inputString);
    }

#ifdef DEBUG
    std::cout << f << " contents:" << std::endl;
    std::cout << inputString << std::endl;
#endif

    f.close();

    generatePictureBySeed(inputString);
}

void generatePictureByFile(std::string filePath, std::string outputFileName)
{
    std::ifstream f;
    f.open(filePath);
    std::string inputString;
    while (f)
    {
        std::getline(f, inputString);
    }

#ifdef DEBUG
    std::cout << f << " contents:" << std::endl;
    std::cout << inputString << std::endl;
#endif

    f.close();

    generatePictureBySeed(inputString, outputFileName);
}

noise::module::Module *getGenerator(int choice)
{
    switch (choice % 9)
    {
    case (0):
        return new noise::module::Checkerboard();
    case (1):
        return new noise::module::Const();
    case (2):
        return new noise::module::Cylinders();
    case (3):
        return new noise::module::RidgedMulti();
    case (4):
        return new noise::module::Spheres();
    case (5):
        return new noise::module::Perlin();
    case (6):
        return new noise::module::Voronoi();
    case (7):
        return new noise::module::Perlin();
    case (8):
        return new noise::module::Billow();
    default:
        std::cout << "YOU SHOULD NOT BE HERE Generator" << std::endl;
        return new noise::module::Perlin();
        // WHAT IS THE 8th CASE I COULD'VE SWORN IT WAS THERE
    }
}

noise::module::Module *getModifier(int choice)
{
    switch (choice % 9)
    {
    case (0):
        return new noise::module::Turbulence();
    case (1):
        return new noise::module::Invert();
    case (2):
        return new noise::module::RotatePoint();
    case (3):
        return new noise::module::ScaleBias();
    case (4):
        return new noise::module::TranslatePoint();
    case (5):
        return new noise::module::Abs();
    case (6):
        return new noise::module::Clamp();
    case (7):
        return new noise::module::Exponent();
    case (8):
        return new noise::module::Abs();
    default:
        std::cout << "BRUTAL MISCALCULATION ON MY (JAKE) PART modifier" << std::endl;
        return new noise::module::Abs();
    }
}

noise::module::Module *getCombiner(int choice)
{
    switch (choice % 4)
    {
    case (0):
        return new noise::module::Add();
    case (1):
        return new noise::module::Min();
    case (2):
        return new noise::module::Max();
    case (3):
        return new noise::module::Multiply();
    case (4):
        return new noise::module::Power();
    default:
        std::cout << "You're not supposed to be here Combiner" << std::endl;
        return new noise::module::Max();
    }
}

#endif