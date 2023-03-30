#pragma once
#include <vector>

#include "color.h"
#include <fstream>
#include <unordered_map>

class image
{
public:

	image()= default;
	image(const char* name, std::vector<unsigned char> p, int w,int h):filename(name),pixels(p), width(w), height(h)
	{}

	const char* filename;
	std::vector<unsigned char> pixels;
	unsigned int width;
	unsigned int height;

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

	void histogram(int n)//is max pixel intensity value
	{
		std::vector<double> number;
		image temp = *this;
		for (int y = height - 1; y > 0; y--)
	
		{
			for (int x = 0; x < width; x++)
			{
				number.push_back((temp(x, y).r/255.)*(n-1));
			}
		}
		//open file for writing
		std::ofstream fw("Histograms\\histogram.txt", std::ofstream::out);


		
		fw << "c(";
		for (int i = 0; i < number.size(); i++)fw << (int)number[i] << ",";
		fw<< ");";
		fw.close();
	}
	

	
};

