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
				if (tempx <0 || tempy<0 || tempy>img.height || tempx>img.width)
					val = Black;//zero padding todo: padding functions
				else
					val = img(tempx, tempy);
				col += f.values[i][j] * val;
			}
	}
	return col;
}