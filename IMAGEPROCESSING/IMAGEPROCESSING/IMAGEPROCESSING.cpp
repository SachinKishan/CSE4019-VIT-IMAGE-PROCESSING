// IMAGEPROCESSING.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#include <iostream>
#include "lodepng.h"
#include "color.h"
#include "image.h"
#include "convolution.h"
#include "pointwiseoperations.h"


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



int main()
{
    std::vector<unsigned char> inputimage; //the raw pixels
    std::vector<unsigned char> outputimage;

	const char* inputfilename = "out1.png";
    const char* outputfilename = "out2.png";
    const auto aspect_ratio = 1;
    unsigned image_width;
	unsigned image_height;

    decodeOneStep(inputfilename,inputimage,image_width,image_height);
    image input(inputfilename, inputimage, image_width, image_height);

    //image resizing
    outputimage.resize(image_width * image_height * 4);

    //processing
    image output(outputfilename, outputimage, input.width, input.height);
    filter f(-1, -1, -1, -1, 9, -1, -1, -1, -1);
    for(int y=image_height-1;y>0;y--)
    {
	    for(int x=1;x<image_width;x++)
	    {
			//todo: allow every pixel to be colored in some color depending on the operation used
            //color c = convolution(input, x, y, f);
            color c = median_filter(input,x,y);
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
