// IMAGEPROCESSING.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#include <iostream>
#include "lodepng.h"
#include "color.h"
#include "image.h"
#include "convolution.h"
#include "pointwiseoperations.h"
#include "frequency.h"

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
    std::vector<unsigned char> input1pixels; //the raw pixels
    std::vector<unsigned char> outputimage;
    std::vector<unsigned char> input2pixels;

	const char* input1filename = "input.png";
	const char* input2filename = "1BitGolemLGTw.png";
    const char* outputfilename = "output.png";
    
    unsigned image_width;
	unsigned image_height;

    decodeOneStep(input1filename,input1pixels,image_width,image_height);
    //decodeOneStep(input2filename,input2pixels,image_width,image_height);
    image input1(input1filename, input1pixels, image_width, image_height);
    //image input2(input2filename, input2pixels, image_width, image_height);

    //image resizing
    outputimage.resize(image_width * image_height * 4);

    //processing
    image output(outputfilename, outputimage, input1.width, input1.height);

    for (int y = image_height - 1; y>0; y--)
    {
	    for(int x=0;x<image_width;x++)
	    {
            color c = contrast_stretching(color_to_greyscale(input1(x, y)),0,255,127,200);
	    	output.colorIn(x, y, input1(x,y));
	    }
    }
    output.histogram();
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
