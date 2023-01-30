#pragma once

#include <algorithm>
class filter//radius will always be three- for convenience
{
public:
    double values[3][3] = { {1,1,1},{1,1,1},{1,1,1} };

    filter
    (double a, double b, double c,
        double d, double e, double f,
        double g, double h, double i)
    {
        values[0][0] = a;
        values[0][1] = b;
        values[0][2] = c;
        values[1][0] = d;
    	values[1][1] = e;
        values[1][2] = f;
        values[2][0] = g;
        values[2][1] = h;
        values[2][2] = i;
       
    }
};

inline color median_filter(image img, int x, int y)//only applies to grayscale images
{
    int tempx, tempy;
    color val,temp;
    std::vector<double> vals;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tempx = x - (i - 1);//x-the i value should flip it
            tempy = y - (j - 1);//same flip for y, means convolution will take place instead f correlation
            if (tempx <= 0 || tempy <= 0 || tempy >= img.height || tempx >= img.width)
                vals.push_back(0);//zero padding todo: padding functions
            else
                vals.push_back(img(tempx, tempy).r);

        }
    }

    std::sort(std::begin(vals), std::end(vals));

    return color(vals[4]);
}

