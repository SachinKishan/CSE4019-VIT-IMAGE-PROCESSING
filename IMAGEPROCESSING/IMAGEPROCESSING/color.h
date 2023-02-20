#pragma once

class color
{
public:
	double r, g, b;
	color() :r(0), g(0), b(0) {}
	color(double _r,double _g, double _b) :r(_r), g(_g), b(_b) {}
	color(double c0) :r(c0), g(c0), b(c0) {}
	color operator-()const { return color(-r, -g, -b); }
	
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

	color& operator/=(const color& c)
	{
		r /= c.r;
		g /= c.g;
		b /= c.b;
		return *this;
	}

	color& operator+(double a)
	{
		r += a;
		g += a;
		b += a;
		return *this;
	}

	color& operator/=(const double t) {
		return *this *= 1 / t;
	}

	bool operator>(double a)
	{
		return r > a && g > a && b > a;
	}
	bool operator<(double a)
	{
		return r < a && g < a && b < a;
	}
	bool operator==(double a)
	{
		return r == a && g == a && b == a;
	}
	bool operator>=(double a)
	{
		return r >= a && g >= a && b >= a;
	}
	bool operator<=(double a)
	{
		return r <= a && g <= a && b <= a;
	}

};

//some color additions
const color Black = color(0);
const color White = color(255);
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

inline color operator/(color v, color t) {
	v.r /= t.r;
	v.b /= t.b;
	v.g /= t.g;
	return v;
}

color RGB_to_HSV(color col)
{
	
	double R = col.r / 255.0;
	double G = col.g / 255.0;
	double B = col.b / 255.0;
	double cmax = std::max(R, std::max(G, B)); 
	double cmin = std::min(R, std::min(G, B)); 
	double diff = cmax - cmin; 
	double h = -1, s = -1;
	if (cmax == cmin)
		h = 0;
	else if (cmax == R)
		h = fmod(60 * ((G - B) / diff) + 360, 360);
	else if (cmax == G)
		h = fmod(60 * ((B - R) / diff) + 120, 360);

	else if (cmax == B)
		h = fmod(60 * ((R - G) / diff) + 240, 360);

	if (cmax == 0)
		s = 0;
	else
		s = (diff / cmax) * 100;

	 double v = cmax * 100;
	 
	return color(h,s,v);
}

color HSVtoRGB(double H, double S, double V) {
	if (H > 360 || H < 0 || S>100 || S < 0 || V>100 || V < 0) {
		return Black;
	}
	double s = S / 100;
	double v = V / 100;
	double C = s * v;
	double X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
	double m = v - C;
	double r, g, b;
	if (H >= 0 && H < 60) {
		r = C, g = X, b = 0;
	}
	else if (H >= 60 && H < 120) {
		r = X, g = C, b = 0;
	}
	else if (H >= 120 && H < 180) {
		r = 0, g = C, b = X;
	}
	else if (H >= 180 && H < 240) {
		r = 0, g = X, b = C;
	}
	else if (H >= 240 && H < 300) {
		r = X, g = 0, b = C;
	}
	else {
		r = C, g = 0, b = X;
	}

	double R= (r + m) * 255;
	double G = (g + m) * 255;
	double B = (b + m) * 255;
	
	return color(R, G, B);
}



inline color log_color(color col)
{
	return color(log(col.r), log(col.g), log(col.b));
}

inline color exp_color(color col)
{
	return color(exp(col.r), exp(col.g), exp(col.b));
}
