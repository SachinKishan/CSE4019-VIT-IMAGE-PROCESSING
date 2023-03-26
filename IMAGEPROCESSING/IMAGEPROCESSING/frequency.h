#pragma once
#include "image.h"
# define M_PI 3.14159265358979323846  /* pi */

double C(int k)
{
	if (k == 0)return 1 / sqrt(2);
	else return 1;
}

double DCT(image f,int x, int y)
{

	int N = f.width;
	int M = f.height;

	double sum=0;

	for (double j = M - 1; j > 0; j--)
	{
		for (double i = 1; i < N; i++)
		{
			sum += f(i, j).r * cos(((2. * i + 1.) * x * M_PI) / (2 * N)) * cos(((2. * j + 1.) * y * M_PI) / (2 * M));
		}
	}
	/*
	std::cout << std::endl;
	std::cout << sum;
	std::cout << std::endl;
	std::cout << "C(x): "<<C(x);
	std::cout << std::endl;
	std::cout << "C(y): "<<C(y);
	*/
	double val = ((double)2 / (double)N) * C(x) * C(y) * sum;
	//std::cout << "val: " << val;
	if (val < 0)val = 0;
	return val;
}

double IDCT(image F, int x, int y)
{
	int N = F.width;
	int M = F.height;

	double sum = 0;

	for (double j = M - 1.; j > 0; j--)
	{
		for (double i = 0; i < N; i++)
		{
			sum += F(i, j).r*C(i) * C(j) * cos(((2. * x + 1.) * i * M_PI) / (2. * N)) * cos(((2. * y + 1.) * j * M_PI) / (2. * M));
		}
	}
	/*
	std::cout << std::endl;
	std::cout << sum;
	std::cout << std::endl;
	std::cout << "C(x): "<<C(x);
	std::cout << std::endl;
	std::cout << "C(y): "<<C(y);
	*/
	double val = ((double)2 / (double)N) *  sum;
	//std::cout << "val: " << val;
	if (val < 0)val = 0;
	return val;
}
