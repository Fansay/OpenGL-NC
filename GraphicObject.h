#ifndef GRAPHICOBJECT_H
#define GRAPHICOBJECT_H

class GraphicObject {
protected:
	//empty
public:
	virtual int update() { return 0; }; //When update is called it does a check for its continued existance. If return is negative it is removed from list and not drawn.
	virtual void draw() {};
};

#endif
