#pragma once

#include <algorithm>
//Todo: add  4x4,5x5 filter classes too 
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

color padding_zero()
{
    return Black;
}

color padding_one()
{
    return White;
}

//the following filters assume we work with grayscale images only
inline color median_filter(image img, int x, int y)
{
    int tempx, tempy;
    color val,temp;
    std::vector<double> vals;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            tempx = x - (i);//x- i should flip the filter
            tempy = y - (j);//same flip for y, this means convolution will take place instead of correlation
            if (tempx <= 0 || tempy <= 0 || tempy >= img.height || tempx >= img.width)
                vals.push_back(padding_zero().r);//zero padding
            else
                vals.push_back(img(tempx, tempy).r);

        }
    }

    std::sort(std::begin(vals), std::end(vals));

    return color(vals[4]);
}

inline color arithmetic_mean_filter(image img, int x, int y, int n/*size of filter*/)
{
    int tempx, tempy;
    color val = Black;
    for (int i = -n/2; i < n/2; i++)
    {
        for (int j = -n/2; j < n/2; j++)
        {
            tempx = x + i;
            tempy = y + j;
            if (tempx <= 0 || tempy <= 0 || tempy >= img.height || tempx >= img.width)val += padding_zero();
            else val += img(i, j);
        }
    }
    val /= n*n;//divide the final sum of all color values by the number of values in the filter, which is n x n 
    return val;
}

color geometry_filter(image img, int x, int y, int n/*size of filter*/)
{
    int tempx, tempy;
    color val = Black;
    for (int i = -n / 2; i < n / 2; i++)
    {
        for (int j = -n / 2; j < n / 2; j++)
        {
            tempx = x + i;
            tempy = y + j;
            if (tempx <= 0 || tempy <= 0 || tempy >= img.height || tempx >= img.width)val *= padding_one();
            else val *= img(i, j);
        }
    }
    int a =pow(val.r,1/(n*n));//power the final sum of all color values by the number of values in the filter, which is n x n 
    return a;
}

color harmonic_filter(image img, int x, int y, int n/*size of filter*/)
{
    int tempx, tempy;
    color val = Black;
    for (int i = -n / 2; i < n / 2; i++)
    {
        for (int j = -n / 2; j < n / 2; j++)
        {
            tempx = x + i;
            tempy = y + j;
            if (tempx <= 0 || tempy <= 0 || tempy >= img.height || tempx >= img.width)val *= padding_one();
            else val += color(White) / img(i, j);
        }
    }
    val = color(n * n)/(val);//divide the final sum of all color values by the number of values in the filter, which is n x n 
    return val;
}

color contraharmonic_mean_filter(image img, int x, int y)
{

}

color max_filter(image img, int x, int y, int n/*size of filter*/)
{
    int tempx, tempy;
    color max = Black;
    color val;
    for (int i = -n / 2; i < n / 2; i++)
    {
        for (int j = -n / 2; j < n / 2; j++)
        {
            tempx = x + i;
            tempy = y + j;
            if (tempx <= 0 || tempy <= 0 || tempy >= img.height || tempx >= img.width)val = padding_zero();
            else val=img(tempx, tempy);
            if (max < img(tempx, tempy).r)max = val;
        }
    }
    return max;
}

color min_filter(image img, int x, int y, int n/*size of filter*/)
{
    int tempx, tempy;
    color min = White;
    color val;
    for (int i = -n / 2; i < n / 2; i++)
    {
        for (int j = -n / 2; j < n / 2; j++)
        {
            tempx = x + i;
            tempy = y + j;
            if (tempx <= 0 || tempy <= 0 || tempy >= img.height || tempx >= img.width)val = padding_one();
            else val = img(tempx, tempy);
            if (min > img(tempx, tempy).r)min = val;
        }
    }
    return min;
}

color midpoint_filter(image img, int x, int y, int n/*size of filter*/)
{
    color max = max_filter(img, x, y, n);
    color min = min_filter(img, x, y, n);
    return (max + min) / 2;
}

color alpha_trimmed_mean_filter(image img, int x, int y, int d, int n/*size of filter*/)
{

}
