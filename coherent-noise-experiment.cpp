#include <iostream>
#include <fstream>
#include <tgmath.h>

double integerNoise(int n)
{
	n = (n >> 13) ^ n;
	int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
	return 1.0 - ((double)nn / 1073741824.0);
}

double coherentNoise(double x)
{
	double CoherentNoise(double x)
	int intX = (int)(floor(x));
	double n0 = integerNoise(intX);
	double n1 = integerNoise(intX + 1);
	double weight = x - std::floor(x);
	double noise = std::lerp(n0, n1, SCurve(weight));
	return noise;
}

int main()
{

	std::ofstream outputFile("coherentNoise.txt");

	for (double i = 0.0; i < 10; i += 0.1)
	{
		outputFile << i << "\t" << integerNoise(i) << std::endl;
	}

	outputFile.close();

	return 0;
}
