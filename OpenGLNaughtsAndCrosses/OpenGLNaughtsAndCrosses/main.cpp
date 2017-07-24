#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

#include "GLGrid.h"
#include "ImageImport.h"

bool right = false;
bool left = false;
bool up = false;
bool down = false;
double horizontal = 0;
double vertical = 0;
bool mouse = false;
bool stop = false;

GLGrid grid;

//Keypress function
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {  //Options are:  GLFW_REPEAT, GLFW_PRESS, GLFW_RELEASE
		left = true;
	}
	else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
		left = false;
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
		right = true;
	}
	else if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
		right = false;
	}

	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		up = true;
	}
	else if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {
		up = false;
	}

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		down = true;
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
		down = false;
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		stop = true;
	}
	else if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
		stop = false;
	}
}
//Only receive 1 input at a time. Need to record when pressed/released and update continually after change of state.

void updatePos() {
	if (up == true) {
		vertical += 0.0001;
	}
	if (down == true) {
		vertical -= 0.0001;
	}

	if (right == true) {
		horizontal += 0.0001;
	}
	if (left == true) {
		horizontal -= 0.0001;
	}

	if (stop == true) {
		horizontal = 0;
		vertical = 0;
	}

	glTranslatef(horizontal, vertical, 0.f);
	grid.adjustPosition(horizontal, vertical);
} //Updates position of 'square' influenced by arrow keys

void draw(){
	//Drawing shape
	glBegin(GL_QUADS);
	glColor3f(1.f, 0.f, 0.f); //Current colour
	glVertex3f(-0.6f, -0.6f, 0.f); //Position of the corner in 3D space
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.6f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.6f, 0.6f, 0.f);
	glColor3f(0.f, 0.f, 0.f);
	glVertex3f(-0.6f, 0.6f, 0.f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.6f, -0.6f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.6f, 0.f);
	glColor3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, (float)-sqrt(0.6*0.6 * 2), 0.f);
	glEnd();
}

//Will draw circle at mouse location
void drawCircle(double mousePosX, double mousePosY) {
	int angle = 0;
	double radius = 0.1;

	glColor3f(1.f, 1.f, 1.f);
	glBegin(GL_LINES);
	while (angle < 360) {
		
		glVertex3f(mousePosX, mousePosY, 0.f);
		glVertex3f(mousePosX + radius*sin(angle), mousePosY + radius*cos(angle), 0.f);


		angle++;
	}
	glEnd();

	glColor3f(0.f, 0.f, 0.f);
	glBegin(GL_LINES);
	glVertex3f(mousePosX, mousePosY + radius / 2, 0.f);
	glVertex3f(mousePosX, mousePosY - radius / 2, 0.f);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(mousePosX + radius / 2, mousePosY, 0.f);
	glVertex3f(mousePosX - radius / 2, mousePosY, 0.f);
	glEnd();
}

void mouseClick(GLFWwindow* window, int button, int action, int mods) {

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		mouse = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		mouse = false;
	}
		
}

int main(int argc, char ** argv){
	if (!glfwInit()){
		exit(EXIT_FAILURE);
	}

	ImageImport image = ImageImport("ANGRY.bmp");

	GLFWwindow *window = glfwCreateWindow(640, 480, "Naughts & Crosses", NULL, NULL);
	if (!window){
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback); //When key press

	/*
	//create a grid
	grid = GLGrid(-1, 1, 1, -1);
	grid.setGridSize(3, 3, 0.01);
	grid.setBackgroundColour(1, 1, 0);
	int arraySize = 5;
	float colourArray[][4] = { { 1,0,0,1 },{ 0,1,0,1 },{ 0,0,1,1 },{ 0,1,1,1 },{ 1,0,1,1 } }; //Easier, but doesn't work well for looped colour picking
	grid.setGridColour(colourArray, arraySize);*/
	/*float **colourArray = new float*[2];
	colourArray[0] = new float[4];
	colourArray[0][0] = 1;
	colourArray[0][1] = 0;
	colourArray[0][2] = 0;
	colourArray[0][3] = 1;
	colourArray[1] = new float[4];
	colourArray[1][0] = 0;
	colourArray[1][1] = 1;
	colourArray[1][2] = 0;
	colourArray[1][3] = 1;*/

	/*
	grid = GLGrid(-1, 1, 1, -1);
	grid.setGridSize(3, 3, 0.01);
	grid.setBackgroundColour(1, 1, 0);*/

	char **gridPattern = new char*[3];
	gridPattern[0] = new char[3];
	gridPattern[0][0] = 0; //angry
	gridPattern[0][1] = 0; //angry
	gridPattern[0][2] = 1; //happy
	gridPattern[1] = new char[3];
	gridPattern[1][0] = 1; //happy
	gridPattern[1][1] = 0; //angry
	gridPattern[1][2] = 1; //happy
	gridPattern[2] = new char[3];
	gridPattern[2][0] = 1; //happy
	gridPattern[2][1] = 1; //happy
	gridPattern[2][2] = 0; //angry

	grid = GLGrid(-1, 1, 1, -1, gridPattern, 3, 3);
	grid.setTexNum(2);
	grid.addTexture(image);
	image = ImageImport("HAPPY.bmp");
	grid.addTexture(image);
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	float trans = 0;
	float ratio;
	int width, height;
	double mousePosX, mousePosY;
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0){
		glfwGetFramebufferSize(window, &width, &height); //Return the window size to 'width' and 'height'
		ratio = width / (float)height;
		glViewport(0, 0, width, height); //Set the draw area size (same as window size)
		//Previous code needs to be in loop to allow draw area to resize with window

		glMatrixMode(GL_PROJECTION); //Which matrix is the current one (projection stack)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear buffer (buffers currently enabled for color writing).
		glLoadIdentity(); //Loads the identity matrix (clears matrix)
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f); //multiply current matrix by an orthographic matrix (makes it display properly in 2D) ... this is where it is set to scale off the height
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f); //Rotates about a specified axis a specified angle glfwGetTime is used to get time since running and have a rate of rotation
		//^^^ rotates everything drawn after it. Same probably applies to translate.

		updatePos();
		//draw();
		//grid.drawGrid();
		glfwGetCursorPos(window, &mousePosX, &mousePosY); //polls cursour position, pixels from top left corner.
		glfwSetMouseButtonCallback(window, mouseClick);
		if (mouse == true) {
			float cellX, cellY;
			grid.findCellCentre((mousePosX / (float)width - 0.5) * 2 * ratio, -(mousePosY / (float)height - 0.5) * 2, &cellX, &cellY);
			if (cellX != NULL && cellY != NULL) {
				//std::cout << cellX << " " << cellY << "\n\n";
				drawCircle(cellX, cellY);
			}

			//std::cout << cellX << " " << cellY << std::endl;
		}
		grid.draw();
		drawCircle((mousePosX/(float)width - 0.5)*2*ratio, -(mousePosY/(float)height - 0.5)*2); //This works for following mouse
		
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}