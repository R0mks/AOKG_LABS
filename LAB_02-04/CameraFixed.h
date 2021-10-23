#ifndef  CAMERAFIXED_H
#define  CAMERAFIXED_H
#include <windows.h>
#include <GL/freeglut.h>
#include <GLM/glm.hpp>
//#include <GLM/gtc/matrix_transform.hpp>
class CameraFixed {
private:
	glm::vec3 cameraRight, cameraDirection, cameraPos, cameraFront, cameraUp;
	GLdouble radius, yaw, pitch;
	bool moveLeft, moveRight,
		 moveUp, moveDown,
		 zoomIn, zoomOut;
	void setVectorAndMoveValues();
	void updateCameraCords();
public:
	GLdouble speed = 90.0;
	CameraFixed();
	CameraFixed(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
	~CameraFixed(void);
	void setKey(bool, bool, bool, bool, bool, bool);
	void simulate(double);
	void apply();
};
#endif