#pragma once
#include <algorithm>
#include <cmath>

double euclid( int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

}

double chessboard(int x1, int y1, int x2, int y2)
{
	return std::max(abs(x1 - x2), abs(y1 - y2));
}

double block(int x1, int y1, int x2, int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
}
