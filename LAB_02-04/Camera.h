#ifndef  CAMERA_H
#define  CAMERA_H
#include <windows.h>
#include <GL/freeglut.h>
class Camera {
private:
	GLdouble eyeX, eyeY, eyeZ;
	GLdouble cenX, cenY, cenZ;
	GLdouble upX, upY, upZ;
	GLdouble radius, yaw, pitch;
	bool moveLeft, moveRight,
		 moveUp, moveDown,
		 zoomIn, zoomOut;
	void setVectorAndMoveValues();
	void updateCameraCords();
public:
	GLdouble speed = 90.0;
	Camera();
	Camera(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
	~Camera(void);
	void setKey(bool, bool, bool, bool, bool, bool);
	void simulate(double);
	void apply();
};
#endif