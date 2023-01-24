#pragma once
#include <vector>

#include "color.h"

class image
{
public:

	image()= default;
	image(const char* name, std::vector<unsigned char> p, int w,int h):filename(name),pixels(p), width(w), height(h)
	{}

	const char* filename;
	unsigned int width;
	unsigned int height;
	std::vector<unsigned char> pixels;

	color operator()(int x,int y)const
	{
		const int val = 4 * width * (height - y) + 4 * x;
		color col;
		col.r = pixels[val];
		col.g = pixels[val+1];
		col.b = pixels[val+2];
		//std::cout << "color:" << " " << col<<std::endl;
		return col;
	}

	void colorIn(int x,int y,color c)
	{
		int val = 4 * width * (height - y) + 4 * x;
		//allot color
		pixels[val] = c.r;
		pixels[val + 1] = c.g;
		pixels[val + 2] = c.b;
		pixels[val + 3] = 255;//alpha value of 1
	}

	
};
