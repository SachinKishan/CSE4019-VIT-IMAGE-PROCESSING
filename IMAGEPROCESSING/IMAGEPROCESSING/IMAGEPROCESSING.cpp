// IMAGEPROCESSING.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "lodepng.h"

//todo
/**
 *  Add image reader for ppm
 *  Add image reader for png
 *  Add method to read everything to grayscale
 *  Add point operations
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

int main()
{
    std::vector<unsigned char> inputimage; //the raw pixels
    std::vector<unsigned char> outputimage;

	const char* inputfilename = "input.png";
    const char* outputfilename = "output.png";
    const auto aspect_ratio = 1;
    unsigned image_width;
	unsigned image_height;
    decodeOneStep(inputfilename,inputimage,image_width,image_height);
	int total = image_width * image_height;

    outputimage = inputimage;



    //image resizing
    outputimage.resize(image_width * image_height * 4);

	encodeOneStep(outputfilename, outputimage, image_width, image_height);
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
