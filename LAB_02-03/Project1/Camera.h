#ifndef  CAMERA_H
#define  CAMERA_H
#include <windows.h>
#include <GL/freeglut.h>
class Camera {
private:
	GLdouble eyeX, eyeY, eyeZ;
	GLdouble cenX, cenY, cenZ;
	GLdouble upX, upY, upZ;
	bool moveLeft, moveRight,
		 moveUp, moveDown,
		 zoomIn, zoomOut;
	void setVectorAndMoveValues();
public:
	Camera();
	Camera(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
	~Camera(void);
	void setKey(bool, bool, bool, bool, bool, bool);
	void simulate(double);
	void apply();
};
#endif