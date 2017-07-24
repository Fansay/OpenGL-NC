#include <iostream>
#include <string>
#include <fstream>

#include "ImageImport.h"

ImageImport::ImageImport(char* text) {
	std::ifstream file(text);
	if (!file) {
		std::cout << "Error opening the file" << std::endl;
	}

	//endianness check
	char flip;
	memcpy(&flip, &endianness, 1);
	if ((int)flip == 1) {
		endianness = 0; //little
	}

	int byteTraversal = 0; //how many bytes through our image file we are

	//if bitmap
	char input[10];
	file.read(input, 2); //grab type
	byteTraversal += 2;
	input[2] = '\0';
	type = input;

	file.read(input, 8); //read and discard next 8Bytes
	byteTraversal += 8;
	file.read(input, 4); //address of start of pixel data
	byteTraversal += 4;
	if (endianness == 1) {
		flip = input[0]; //to flip all the bytes from little-endian to big-endian (stored as little in BMP)
		input[0] = input[3];
		input[3] = flip;
		flip = input[1];
		input[1] = input[2];
		input[2] = flip;
	}
	memcpy(&offset, input, 4); //turns out machine is little-endian (YAY!)
	std::cout << "offest " << offset << std::endl;

	//Get DIB header size
	file.read(input, 4);
	byteTraversal += 4;
	if (endianness == 1) {
		flip = input[0]; //to flip all the bytes from little-endian to big-endian (stored as little in BMP)
		input[0] = input[3];
		input[3] = flip;
		flip = input[1];
		input[1] = input[2];
		input[2] = flip;
	}
	memcpy(&DIBSize, input, 4);
	std::cout << DIBSize << std::endl;


	//Get Width and Height of the image
	if (DIBSize == 12) { //only 2 that really matter
		//Width
		file.read(input, 2);
		byteTraversal += 2;
		input[2] = 0;
		input[3] = 0;
		if (endianness == 1) {
			flip = input[0]; //to flip all the bytes from little-endian to big-endian (stored as little in BMP)
			input[0] = input[3];
			input[3] = flip;
			flip = input[1];
			input[1] = input[2];
			input[2] = flip;
		}
		memcpy(&imageWidth, input, 4);

		//Height
		file.read(input, 2);
		byteTraversal += 2;
		input[2] = 0;
		input[3] = 0;
		if (endianness == 1) {
			flip = input[0]; //to flip all the bytes from little-endian to big-endian (stored as little in BMP)
			input[0] = input[3];
			input[3] = flip;
			flip = input[1];
			input[1] = input[2];
			input[2] = flip;
		}
		memcpy(&imageHeight, input, 4);
	}
	else if (DIBSize == 40) { //Think all others use 4Bytes, so could be else
		//Width
		file.read(input, 4);
		byteTraversal += 4;
		if (endianness == 1) {
			flip = input[0]; //to flip all the bytes from little-endian to big-endian (stored as little in BMP)
			input[0] = input[3];
			input[3] = flip;
			flip = input[1];
			input[1] = input[2];
			input[2] = flip;
		}
		memcpy(&imageWidth, input, 4);

		//Height
		file.read(input, 4);
		byteTraversal += 4;
		if (endianness == 1) {
			flip = input[0]; //to flip all the bytes from little-endian to big-endian (stored as little in BMP)
			input[0] = input[3];
			input[3] = flip;
			flip = input[1];
			input[1] = input[2];
			input[2] = flip;
		}
		memcpy(&imageHeight, input, 4);
	}

	//Get Bits per pixel
	file.read(input, 2); //Read and discard
	byteTraversal += 2;
	file.read(input, 2);
	byteTraversal += 2;
	input[2] = 0;
	input[3] = 0;
	if (endianness == 1) {
		flip = input[0]; //to flip all the bytes from little-endian to big-endian (stored as little in BMP)
		input[0] = input[3];
		input[3] = flip;
		flip = input[1];
		input[1] = input[2];
		input[2] = flip;
	}
	memcpy(&bpp, input, 4);
	//std::cout << imageWidth << std::endl;
	//std::cout << imageHeight << std::endl;
	//std::cout << bpp << std::endl;


	//Store pixel data into array as is. OpenGL should be able to unpack in correct order
	int imageSize = (bpp*imageWidth + 31) / 32 * 4;
	if (imageHeight > 0) {
		imageSize = imageSize*imageHeight;
		std::cout << "image size " << imageSize << std::endl;
	}
	else {
		imageSize = imageSize*-imageHeight;
		std::cout << "image size " << imageSize << std::endl;
	}

	//Grab unwanted bytes into input 10 at a time
	int i = offset - byteTraversal;
	for (; i > 10; i -= 10) {
		file.read(input, 10);
		byteTraversal += 10;
	}
	file.read(input, i); //discard rest of bytes
	byteTraversal += i;

	std::cout << "bytes" << byteTraversal << std::endl;

	pixelData = (char*)malloc(imageSize);
	file.read(pixelData, imageSize);
	file.close();
}

void ImageImport::freeImage() {
	free(pixelData);
}

//Getters
char* ImageImport::getPixelData() {
	return pixelData;
}

int ImageImport::getImageWidth() {
	return imageWidth;
}

int ImageImport::getImageHeight() {
	return imageHeight;
}

int ImageImport::getBitsPerPixel() {
	return bpp;
}

std::string ImageImport::getType() {
	return type;
}