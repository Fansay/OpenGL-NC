#ifndef IMAGEIMPORT_H
#define IMAGEIMPORT_H

class ImageImport {
private:
	int endianness = 1; //0 = little, 1 = big
	std::string type; //image file type
	unsigned int offset = 0; //offset (address of start of image data)
	int DIBSize = 0; //size of DIB header (determines size of other fields)
	int imageWidth = 0;
	int imageHeight = 0;
	int bpp = 0; //bits per pixel
	char *pixelData;
	
public:
	ImageImport(char* imageToRead);
	void freeImage();

	//Getters
	char* getPixelData();
	int getImageWidth();
	int getImageHeight();
	int getBitsPerPixel();
	std::string getType();
};

#endif