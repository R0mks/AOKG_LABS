#ifndef  GRAPHICOBJECT_H
#define  GRAPHICOBJECT_H
#include <windows.h>
#include <GL/freeglut.h>
#include <ostream>
struct pos {
	GLfloat x;
	GLfloat y;
	GLfloat z;
};
struct colorRGB {
	GLfloat R;
	GLfloat G;
	GLfloat B;
};
class GObject {
private:
	pos position;
	colorRGB color;
	GLfloat angle;
	GLfloat size;
public:
	GObject();
	GObject(GLfloat *pos, GLfloat ang, GLfloat *color, GLfloat size = 1.0f);
	void setPosition(GLfloat x, GLfloat y, GLfloat z);
	void setAngle(GLfloat ang);
	void setColor(GLfloat r, GLfloat g, GLfloat b);
	void setSize(GLfloat size);
	void draw(void);
	friend std::ostream& operator<<(std::ostream&, const GObject);
};
#endif