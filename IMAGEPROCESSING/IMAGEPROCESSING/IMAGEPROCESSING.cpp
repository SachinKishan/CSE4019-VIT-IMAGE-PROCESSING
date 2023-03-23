// IMAGEPROCESSING.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#include <iostream>
#include "lodepng.h"
#include "color.h"
#include "image.h"
#include "convolution.h"


const int MAX_COLOR_VALUE = 255;
const int MIN_COLOR_VALUE = 0;


//todo
/**
 *  Add method to read everything to grayscale
 *  Add point operations
 *  Add convolutions
 *  
 *
 *
 *  
 */

#pragma region PNG
void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned &width, unsigned &height) {
    //Encode the image
    unsigned const error = lodepng::encode(filename, image, width, height);

    //if there's an error, display it
    if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}

void decodeOneStep(const char* filename,  std::vector<unsigned char>& image, unsigned& width, unsigned& height) {

    //decode
    unsigned error = lodepng::decode(image, width, height, filename);

    //if there's an error, display it
    if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}
#pragma endregion


void color_image_pixel(std::vector<unsigned char> &image,int x,int y, color c, unsigned image_width, unsigned image_height)
{

    //const unsigned char rf = static_cast<unsigned char>(std::min(1., c.r) * 255);
    //const unsigned char gf = static_cast<unsigned char>(std::min(1., c.g) * 255);
    //const unsigned char bf = static_cast<unsigned char>(std::min(1., c.b) * 255);

    int val = 4 * image_width * (image_height - y) + 4 * x;
    //allot color
    image[val] = c.r;
    image[val + 1] = c.g;
    image[val + 2] = c.b;
    image[val + 3] = 255;//alpha value of 1
}



color color_to_greyscale(color c)
{
    float col = (0.3 * c.r) + (0.59 * c.g) + (0.11 * c.b);
    return col;
}

inline double random_double() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max - min) * random_double();
}


color contrast(color c)
{
    return MAX_COLOR_VALUE - c;
}

color thresholding(color c, int m)
{
    if (c >= m)return c;
    else return 0;
}


double_t value_component_enhancement(double v, double vbar,double Vmax)
{
    double vdash = log((v / vbar) + 1) / log((Vmax/vbar)+1);
    return vdash;
}

void k_means(image &img )
{
    color k1=img(
        img.width/2,
        img.height/2);

    color k2 = img(
        img.width / 4,
        img.height / 4);
    color m1, m2, m1old, m2old;
    std::vector<int> cluster(img.height*img.width);
	int val = 0;
    int iter = 0;
    int maxiteration = 100; 
    int n1 = 0, n2 = 0;
    while (iter < maxiteration)
    {
        for (int j = img.height - 1; j > 0; j--)
        {
            for (int i = 1; i < img.width; i++)
            {
                val = img.width * (img.height - j) + i;
                if (distance(img(i, j), k1) < distance(img(i, j), k2))
                    cluster[val] = 1;
                else
                    cluster[val] = 2;
            }
        }
        n1 = 0;
        n2 = 0;
        for (int j = img.height - 1; j > 0; j--)
        {
            for (int i = 1; i < img.width; i++)
            {

                val = img.width * (img.height - j) + i;
                if (cluster[val] == 1)
                {
                    m1 += img(i, j);
                    n1++;
                }
                else if (cluster[i] == 2)
                {
                    m2 += img(i, j);
                    n2++;
                }
            }
        }
    	m1 /= n1;
    	m2 /= n2;
        
        if (m1 == m1old && m2 == m2old)break;
        m1old = m1;
        m2old = m2;
        k1 = m1;
        k2 = m2;
    	iter++;
    }
    for (int j = img.height - 1; j > 0; j--)
    {
        for (int i = 1; i < img.width; i++)
        {
            val = img.width * (img.height - j) + i;
            if (cluster[val] == 1)img.colorIn(i, j, k1);
            else if (cluster[val] == 2)img.colorIn(i, j, k2);
        }
    }	    	

	printf("clustering complete %d",iter);
}

int main()
{
    std::vector<unsigned char> inputimage; //the raw pixels
    std::vector<unsigned char> outputimage;
    std::vector<unsigned char> enhancedimage;

	const char* inputfilename = "sky_and_field.png";
    const char* outputfilename = "sky_and_field_enhanced.png";
    const auto aspect_ratio = 1;
    unsigned image_width;
	unsigned image_height;

    decodeOneStep(inputfilename,inputimage,image_width,image_height);
    image input(inputfilename, inputimage, image_width, image_height);

    //image resizing
    outputimage.resize(image_width * image_height * 4);
    enhancedimage.resize(image_width * image_height * 4);

    //processing
    image output(outputfilename, outputimage, input.width, input.height);
    image enhanced_output(outputfilename, enhancedimage, input.width, input.height);

    double Vbar=0;
    double Vmax=0;

    //rgb to hsv
    for (int y = image_height - 1; y > 0; y--)
    {
        for (int x = 1; x < image_width; x++)
        {
            color c =RGB_to_HSV(input(x, y));
            input.colorIn(x, y, (c));
        }
    }

    //finding vmax
    for (int y = image_height - 1; y > 0; y--)
    {
        for (int x = 1; x < image_width; x++)
        {
            if (Vmax < input(x, y).b)Vmax = input(x, y).b;
        }
    }

    //vbar calculation
    for (int y = image_height - 1; y > 0; y--)
    {
        for (int x = 1; x < image_width; x++)
        {
            Vbar += log(input(x, y).b + 0.001);
        }
    }


    const unsigned int N = input.width * input.height;
    Vbar /= N;
    Vbar = exp(Vbar);
    for(int y=image_height-1;y>0;y--)//component enhancement
    {
	    for(int x=1;x<image_width;x++)
	    {
            color c = (input(x, y));
            c.b = value_component_enhancement(c.b, Vbar, Vmax)*100;
            output.colorIn(x, y, c);
	    }
    }
    
   // k_means(enhanced_output);
    for (int y = image_height - 1; y > 0; y--)
    {
        for (int x = 1; x < image_width; x++)
        {
            color c = (output(x, y));
        	c = HSVtoRGB(c.r, c.g, c.b);
            output.colorIn(x, y, (c));
        }
    }
    
	encodeOneStep(output.filename, output.pixels, output.width, output.height);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
