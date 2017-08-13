#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <vector>
class GLFWwindow;
class GraphicObject;

class WindowManager {
private:
	GLFWwindow *window;
	int windowWidth, windowHeight; //640x480
	float x1, x2, y1, y2;
	float ratio; //(float)width/(float)height


	std::vector<GraphicObject> objects;

public:
	WindowManager();
	WindowManager(int width, int height);
	void draw(); //idea of some error giving (can't remember)
	void update(); //update draw area?
	void addObject(GraphicObject go);
	void closeWindow();

	//Setters
	void setWindowHeight(int height);
	void setWindowWidth(int width);
	void setWindowSize(int width, int height); //in pixels
	void setDrawArea(float x1, float x2, float y1, float y2);

	//Getters
	int getWindowHeight();
	int getWindowWidth();
	void getWindowSize(int *width, int *height);
	void getDrawArea(float *x1, float *x2, float *y1, float *y2);
};

#endif