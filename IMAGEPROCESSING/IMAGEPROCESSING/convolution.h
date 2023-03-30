#pragma once
#include "filter.h"
#include "image.h"

//convolution header file
inline color convolution(image img, int x, int y, filter f)
{
	color col;
	color val;
	int tempx, tempy;
	for(int i=0;i<3;i++)
	{
			for(int j=0;j<3;j++)
			{
				tempx = x - (i - 1);//x-the i value should flip it
				tempy = y - (j - 1);//same flip for y, means convolution will take place instead f correlation
				if (tempx <= 0 || tempy<= 0 || tempy>=img.height || tempx>=img.width)
					val = padding_zero();
				else
					val = img(tempx, tempy);
				col += f.values[i][j] * val;
			}
	}
	return col;
}

inline color correlation(image img, int x, int y, filter f)
{
	color col;
	color val;
	int tempx, tempy;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			tempx = x + i;
			tempy = y + j;
			if (tempx <= 0 || tempy <= 0 || tempy >= img.height || tempx >= img.width)
				val = padding_zero();
			else
				val = img(tempx, tempy);
			col += f.values[i+1][j+1] * val;
		}
	}
	return col;
}