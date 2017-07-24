#ifndef GLGRID_H
#define GLGRID_H

#include "GraphicObject.h"

class ImageImport;

class GLGrid : protected GraphicObject{ // --TODO-- adjust so can draw based on desired cell size from the top left corner, and can set some cells to be empty (set alpha to 0, code skips instead of wasting time drawing)
private:
	float x1 = -1; //left horizontal
	float x2 = 1; //right horizontal
	float y1 = 1; //top vertical
	float y2 = -1; //bottom vertical
	int horizontalNum = 0; //number of squares across the horizontal
	int verticalNum = 0; //number of squares across the vertical
	float lineThickness = 0.01f; //spacing between squares of grid
	float gridCellWidth = 0; //cell size
	float gridCellHeight = 0;

	//for colour of background
	float *backgroundColour; //default black, no transparency

	//for colour of grid
	float **gridColour; //default white, no transparency
	int gridArraySize = 1;

	//for grid pattern ..........................................TODO.................allow for empty cell somehow (0 index is empty, just increase indexes by 1)
	char **gridPattern; //2D array of numbers, get texture/colour from (gridColour) or (textureNames) array based on index.
	int patternOn = 0; //1 for on

	//for image grid
	int imagesOn = 0; //1 for on
	GLuint *textureNames;
	int texArraySize = 0; //Number of elements in array
	int texAllocSize = 0; //Allocated size of array, so we can alloc once, then populate

public:
	GLGrid();
	GLGrid(float leftCoordinate, float rightCoordinate, float topCoordinate, float bottomCoordinate);
	GLGrid(float leftCoordinate, float rightCoordinate, float topCoordinate, float bottomCoordinate, char **gridPatternStyle, float numberOfHorizontalCells, float numberOfVerticalCells);
	void adjustPosition(float adjustX, float adjustY); //adjust location of the grid (moves it X,Y)
	void draw(); //draws grid with textures or colours
	int update(); //nothing yet
	void findCellCentre(float coordinateX, float coordinateY, float *cellCentreX, float *cellCentreY); //finds centre of the cell which matches the given coordinates
	void addTexture(ImageImport image);
	void freeGridArray();
	void freeBackgroundArray();
	void freeTexNames();

	//Setters
	void setDrawArea(float leftCoordinate, float rightCoordinate, float topCoordinate, float bottomCoordinate);
	void setGridSize(int numberOfHorizontalCells, int numberOfVerticalCells, float cellSpacing);
	void setGridSize(int numberOfHorizontalCells, int numberOfVerticalCells);
	void setGridSpacing(float cellSpacing);
	void setTexNum(int num); //set before adding textures, also allocs memory and creates texture names
	void setTexOn();
	void setTexOff();
	void setGridColour(float red, float green, float blue, float alpha);
	void setGridColour(float red, float green, float blue);
	void setGridColour(float *RGBArray); //include alpha
	void setGridColour(float **RGBArray, int verticalSize); //include alpha
	void setGridColour(float RGBArray[][4], int verticalSize); //include alpha
	void setBackgroundColour(float red, float green, float blue, float alpha);
	void setBackgroundColour(float red, float green, float blue);
	void setBackgroundColour(float *RGBArray); //include alpha
	void setGridPattern(char **gridPatternStyle, float numberOfHorizontalCells, float numberOfVerticalCells); //2D array of grid pattern, number of cells (horizontal and vertical)
	void setGirdPatternOn(int on); //1 for on, 0 for off

	//Getters
	void getDrawArea(float *leftCoordinate, float *rightCoordinate, float *topCoordinate, float *bottomCoordinate);
	void getGridSize(int *numberOfHorizontalCells, int *numberOfVerticalCells);
	void getCellSize(float *cellWidth, float *cellHeight);
};

#endif