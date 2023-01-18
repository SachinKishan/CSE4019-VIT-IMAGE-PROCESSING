#pragma once

class color
{
public:
	double r, g, b;
	color() :r(0), g(0), b(0) {}
	color(double _r,double _g, double _b) :r(_r), g(_g), b(_b) {}
	color(double c0) :r(c0), g(c0), b(c0) {}
	color operator-()const { return color(-r, -g - , b); }
	
	color& operator+=(const color& c)
	{
		r += c.r;
		g += c.g;
		b += c.b;
		return *this;
	}

	color& operator*=(const color& c)
	{
		r *= c.r;
		g *= c.g;
		b *= c.b;
		return *this;
	}

	color& operator/=(const double t) {
		return *this *= 1 / t;
	}

};

//some color additions
const color Black = color(0);
const color White = color(1);
const color Red = color(1, 0, 0);
const color Blue = color(0, 0, 1);
const color Green = color(0, 1, 0);
const color Brown = color(0.54, 0.26, 0.07);


// color Utility Functions

inline std::ostream& operator<<(std::ostream& out, const color& v) {
	return out << v.r << ' ' << v.g << ' ' << v.b;
}

inline color operator+(const color& u, const color& v) {
	return color(u.r + v.r, u.g + v.g, u.b + v.b);
}

inline color operator-(const color& u, const color& v) {
	return color(u.r - v.r, u.g - v.g, u.b - v.b);
}

inline color operator*(const color& u, const color& v) {
	return color(u.r * v.r, u.g * v.g, u.b * v.b);
}

inline color operator*(double t, const color& v) {
	return color(t * v.r, t * v.g, t * v.b);
}

inline color operator*(const color& v, double t) {
	return t * v;
}

inline color operator/(color v, double t) {
	return (1 / t) * v;
}
