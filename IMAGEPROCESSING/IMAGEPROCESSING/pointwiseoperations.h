#pragma once
#include <cmath>
#include "color.h"


const int MAX_COLOR_VALUE = 255;
const int MIN_COLOR_VALUE = 0;

color negative(color c)
{
    return MAX_COLOR_VALUE - c;
}

inline color thresholding(color c, int m)
{
    if (c >= m)return c;
    else return 0;
}

inline color contrast_stretching(color c, int m)
{
    if (c > m)return MAX_COLOR_VALUE;
    else if (c == m)return c;
    else if (c < m)return 0;
    return 0;
}

inline color contrast_stretching(color c,double r1, double r2, double s1, double s2)
{
    return (c - r1) * ((s2 - s1) / (r2 - r1)) + s1;
}

inline color log_transformation(color c, int maxValue)
{
    const double constant = MAX_COLOR_VALUE / log(1 + maxValue);
    return constant * log(c.r + 1);
}

color gray_level_slicing_without_background(color c, int r1, int r2, int q=0)
{
    if (r1 < c.r && c.r < r2) return r2;
    else return q;
}

color gray_level_slicing_with_background(color c, int r1, int r2)
{
    if (r1 < c.r && c.r < r2) return MAX_COLOR_VALUE;
    else return c;
}

//logical operations- assume binary images

color AND(color c1,color c2)
{
    if (c1.r == 1 && c2.r == 1)return 1;
    else return 0;
}

color OR(color c1, color c2)
{
    if (c1.r == 1 || c2.r == 1)return 1;
    else return 0;
}

color NOT(color c)
{
    if (c.r == 1)return 0;
    else return 1;
}

color XOR(color c1, color c2)
{
    if (c1.r != c2.r == 0)return 1;
    else return 0;
}