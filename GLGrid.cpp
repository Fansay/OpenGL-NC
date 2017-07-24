#include <GLFW/glfw3.h>
#include <iostream>

#include "GLGrid.h"
#include "ImageImport.h"

GLGrid::GLGrid() {
	backgroundColour = new float[4];
	backgroundColour[0] = 0;
	backgroundColour[1] = 0;
	backgroundColour[2] = 0;
	backgroundColour[3] = 1;

	gridColour = new float*[1];
	gridColour[0] = new float[4];
	gridColour[0][0] = 1;
	gridColour[0][1] = 1;
	gridColour[0][2] = 1;
	gridColour[0][3] = 1;

}

GLGrid::GLGrid(float X1, float X2, float Y1, float Y2) {
	x1 = X1;
	x2 = X2;
	y1 = Y1;
	y2 = Y2;

	backgroundColour = new float[4];
	backgroundColour[0] = 0;
	backgroundColour[1] = 0;
	backgroundColour[2] = 0;
	backgroundColour[3] = 1;

	gridColour = new float*[1];
	gridColour[0] = new float[4];
	gridColour[0][0] = 1;
	gridColour[0][1] = 1;
	gridColour[0][2] = 1;
	gridColour[0][3] = 1;
}

GLGrid::GLGrid(float X1, float X2, float Y1, float Y2, char **pattern, float H, float V) {
	x1 = X1;
	x2 = X2;
	y1 = Y1;
	y2 = Y2;

	backgroundColour = new float[4];
	backgroundColour[0] = 0;
	backgroundColour[1] = 0;
	backgroundColour[2] = 0;
	backgroundColour[3] = 1;

	gridColour = new float*[1];
	gridColour[0] = new float[4];
	gridColour[0][0] = 1;
	gridColour[0][1] = 1;
	gridColour[0][2] = 1;
	gridColour[0][3] = 1;

	gridPattern = pattern;
	horizontalNum = H;
	verticalNum = V;

	patternOn = 1;
}

void GLGrid::adjustPosition(float adjustX, float adjustY) {
	x1 += adjustX;
	x2 += adjustX;
	y1 += adjustY;
	y2 += adjustY;
}

void GLGrid::draw() {
	//draw background
	glBegin(GL_QUADS);
	glColor4f(backgroundColour[0], backgroundColour[1], backgroundColour[2], backgroundColour[3]);
	glVertex3f(x1, y1, 0);
	glVertex3f(x1, y2, 0);
	glVertex3f(x2, y2, 0);
	glVertex3f(x2, y1, 0);
	glEnd();

	//Calculate grid cell size
	gridCellHeight = ((y1 - y2) - lineThickness*(verticalNum - 1)) / verticalNum;
	gridCellWidth = ((x2 - x1) - lineThickness*(horizontalNum - 1)) / horizontalNum;

	//x and y coords of grid cells
	float X1;
	float X2;
	float Y1;
	float Y2;

	//draw grid
	int i = 0;
	int j = 0;
	int row = 0;
	while (i < verticalNum) {
		j = 0;
		while (j < horizontalNum) {
			X1 = x1 + (gridCellWidth + lineThickness)*j;
			X2 = x1 + gridCellWidth*(j + 1) + lineThickness*j;
			Y1 = y1 - (gridCellHeight + lineThickness)*i;
			Y2 = y1 - gridCellHeight*(i + 1) - lineThickness*i;

			//std::cout << gridCellHeight << std::endl;
			//std::cout << gridCellWidth << std::endl;
			if (imagesOn) {
				if (patternOn) {
					glBindTexture(GL_TEXTURE_2D, textureNames[gridPattern[i][j]]);
				}
				else {
					glBindTexture(GL_TEXTURE_2D, textureNames[row]); //Select texture to draw
				}
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(X1, Y2, 0);  // Bottom Left Of The Texture and Quad
				glTexCoord2f(1.0f, 0.0f); glVertex3f(X2, Y2, 0);  // Bottom Right Of The Texture and Quad
				glTexCoord2f(1.0f, 1.0f); glVertex3f(X2, Y1, 0);  // Top Right Of The Texture and Quad
				glTexCoord2f(0.0f, 1.0f); glVertex3f(X1, Y1, 0);  // Top Left Of The Texture and Quad
				glEnd();
			}
			else {
				glBegin(GL_QUADS);
				if (patternOn) {
					glColor4f(gridColour[gridPattern[i][j]][0], gridColour[gridPattern[i][j]][1], gridColour[gridPattern[i][j]][2], gridColour[gridPattern[i][j]][3]);
				}
				else{
					glColor4f(gridColour[row][0], gridColour[row][1], gridColour[row][2], gridColour[row][3]);
				}
				glVertex3f(X1, Y1, 0);
				glVertex3f(X1, Y2, 0);
				glVertex3f(X2, Y2, 0);
				glVertex3f(X2, Y1, 0);
				glEnd();
			}

			row++;
			if (imagesOn && row == texArraySize) {
				row = 0;
			}
			else if (!imagesOn && row == gridArraySize) {
				row = 0;
			}

			j++;
		}

		i++;
	}

	glBindTexture(GL_TEXTURE_2D, 0); //unbind texture
}

int GLGrid::update() {
	//nothing yet
	return 0; //success
}

void GLGrid::findCellCentre(float coordX, float coordY, float *cellX, float *cellY) {
	*cellX = NULL;
	*cellY = NULL;

	//x and y coords of grid cells
	float X1;
	float X2;
	float Y1;
	float Y2;

	//find cell that contains given coordinates
	int i = 0;
	int j = 0;
	while (i < verticalNum) {
		j = 0;
		while (j < horizontalNum) {
			X1 = x1 + (gridCellWidth + lineThickness)*j;
			X2 = x1 + gridCellWidth*(j + 1) + lineThickness*j;
			Y1 = y1 - (gridCellHeight + lineThickness)*i;
			Y2 = y1 - gridCellHeight*(i + 1) - lineThickness*i;

			if ((X1 <= coordX) && (X2 >= coordX) && (Y1 >= coordY) && (Y2 <= coordY)) {
				*cellX = (X1 + X2) / 2;
				*cellY = (Y1 + Y2) / 2;
				//std::cout << X1 << " " << X2 << "\n" << Y1 << " " << Y2 << "\n\n";
				break;
			}

			j++;
		}

		if (*cellX != NULL && *cellY != NULL) {
			break;
		}

		i++;
	}
}

void GLGrid::addTexture(ImageImport image) {
	if (texArraySize < texAllocSize) { //setup image
		glBindTexture(GL_TEXTURE_2D, textureNames[texArraySize]);
		texArraySize++;

		glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE); //don't swap bytes in memory (not really needed)
		glPixelStorei(GL_UNPACK_LSB_FIRST, GL_FALSE); //MSB is first
		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0); //could also be set to image size, helps find next row (efficiency improvement?)
		//glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0); //Convenience to programmer, not necessary
		//glPixelStorei(GL_UNPACK_SKIP_ROWS, 0); //Convenience to programmer, not necessary
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4); //DIBs have alignment 4, though default is 4

		if (image.getBitsPerPixel() == 24) { //Two main BMP types, are others, unsupported in my ImageImport class.
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.getImageWidth(), image.getImageHeight(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, image.getPixelData());
		}
		else if (image.getBitsPerPixel() == 32) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getImageWidth(), image.getImageHeight(), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, image.getPixelData());
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //samples image by nearest pixel (something to do with smaller texture than image)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //samples image by nearest pixel (something to do with larger texture than image)
	}
	else {
		std::cout << "Freak out!" << std::endl;
	}

	image.freeImage();
}

void GLGrid::freeGridArray() {
	for (int i = 0; i < gridArraySize; i++) {
		delete gridColour[i];
	}

	delete gridColour;
}

void GLGrid::freeBackgroundArray() {
	delete backgroundColour;
}

void GLGrid::freeTexNames() {
	glDeleteTextures(texAllocSize, textureNames);
	texAllocSize = 0;
}

//Setters
void GLGrid::setDrawArea(float X1, float X2, float Y1, float Y2) {
	x1 = X1;
	x2 = X2;
	y1 = Y1;
	y2 = Y2;
}

void GLGrid::setGridSize(int H, int V, float L) {
	horizontalNum = H;
	verticalNum = V;
	lineThickness = L;
}

void GLGrid::setGridSize(int H, int V) {
	horizontalNum = H;
	verticalNum = V;
}

void GLGrid::setGridSpacing(float L) {
	lineThickness = L;
}

void GLGrid::setTexNum(int num) {
	texAllocSize = num;
	textureNames = (GLuint*)malloc(sizeof(GLuint)*texAllocSize); //alloc room for n texture names
	glGenTextures(texAllocSize, textureNames); //generates n texture names
	imagesOn = 1;
}

void GLGrid::setTexOn() {
	imagesOn = 1;
}

void GLGrid::setTexOff() {
	imagesOn = 0;
}

//Grid colours
void GLGrid::setGridColour(float R, float G, float B, float A) {
	gridColour[0][0] = R;
	gridColour[0][1] = G;
	gridColour[0][2] = B;
	gridColour[0][3] = A;
}

void GLGrid::setGridColour(float R, float G, float B) {
	gridColour[0][0] = R;
	gridColour[0][1] = G;
	gridColour[0][2] = B;
}

void GLGrid::setGridColour(float *RGB) {
	freeGridArray();
	gridColour = new float*[1];
	gridColour[0] = RGB;
}

void GLGrid::setGridColour(float **RGB, int size) {
	freeGridArray();
	gridArraySize = size;
	gridColour = RGB;
}

void GLGrid::setGridColour(float RGB[][4], int size) {
	freeGridArray();
	gridArraySize = size;
	gridColour = new float*[gridArraySize];
	for (int i = 0; i < gridArraySize; i++) {
		gridColour[i] = RGB[i];
	}
}

//Background colours
void GLGrid::setBackgroundColour(float R, float G, float B, float A) {
	backgroundColour[0] = R;
	backgroundColour[1] = G;
	backgroundColour[2] = B;
	backgroundColour[3] = A;
}

void GLGrid::setBackgroundColour(float R, float G, float B) {
	backgroundColour[0] = R;
	backgroundColour[1] = G;
	backgroundColour[2] = B;
}

void GLGrid::setBackgroundColour(float *RGB) {
	freeBackgroundArray();
	backgroundColour = RGB;
}

//Grid Pattern
void GLGrid::setGridPattern(char **pattern, float H, float V) {
	gridPattern = pattern;
	horizontalNum = H;
	verticalNum = V;

	patternOn = 1;
}

void GLGrid::setGirdPatternOn(int on) {
	patternOn = on;
}


//Getters
void GLGrid::getDrawArea(float *X1, float *X2, float *Y1, float *Y2) {
	*X1 = x1;
	*X2 = x2;
	*Y1 = y1;
	*Y2 = y2;
}

void GLGrid::getGridSize(int *H, int *V) {
	*H = horizontalNum;
	*V = verticalNum;
}

void GLGrid::getCellSize(float *cellX, float *cellY) {
	*cellX = gridCellWidth;
	*cellY = gridCellHeight;
}