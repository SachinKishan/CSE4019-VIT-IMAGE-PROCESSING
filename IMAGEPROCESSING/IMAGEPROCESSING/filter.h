#pragma once


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

