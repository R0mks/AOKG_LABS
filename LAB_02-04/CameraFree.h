#ifndef  CAMERAFREE_H
#define  CAMERAFREE_H
#include <windows.h>
#include <GL/freeglut.h>
#include <GLM/glm.hpp>
class CameraFree {
private:
	glm::vec3 cameraPos, cameraFront, cameraUp;
	GLdouble yaw, pitch;
	float lastX, lastY;
	bool moveForward, moveBack, moveLeft, moveRight;
	bool firstMouse;
	void setVectorAndMoveValues();
	void updateCameraCords();
public:
	GLfloat speed = 30.0f;
	GLfloat sensivity = 0.05f;
	CameraFree();
	CameraFree(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	~CameraFree(void);
	void setKey(bool, bool, bool, bool);
	void mouseCallback(int,int);
	void mouseCallbackSaveLastXY(int,int,int,int);
	void getLastXYForCamera();
	void simulate(double);
	void apply();
	void gotoCenter();
	inline bool isFirstMouse();
	inline void setFirstMouse();
};
#endif