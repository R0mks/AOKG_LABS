#ifndef  CAMERA_H
#define  CAMERA_H
#include <windows.h>
#include <GL/freeglut.h>
#include <GLM/glm.hpp>
class Camera {
protected:
	glm::vec3 cameraPos, cameraFront, cameraUp;
	GLdouble radius, yaw, pitch;
	virtual void setVectorAndMoveValues() = 0;
	virtual void updateCameraCords() = 0;
public:
	GLfloat speed;
	Camera();
	~Camera();
	virtual void simulate(double) = 0;
	virtual void apply() = 0;
};
class CameraFree : protected Camera{
private:
	float lastX, lastY;
	bool moveForward, moveBack, 
		moveLeft, moveRight;
	bool firstMouse;
	virtual void setVectorAndMoveValues();
	virtual void updateCameraCords();
public:
	GLfloat sensivity = 0.05f;
	CameraFree();
	CameraFree(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	~CameraFree();
	virtual void simulate(double);
	virtual void apply();
	void setKey(bool, bool, bool, bool);
	void mouseCallback(int,int);
	void mouseCallbackSaveLastXY(int,int,int,int);
	void getLastXYForCamera();
	void gotoCenter();
	inline bool isFirstMouse();
	inline void setFirstMouse();
};
class CameraFixed : protected Camera{
protected:
	bool moveLeft, moveRight,
		moveUp, moveDown,
		zoomIn, zoomOut;
	virtual void setVectorAndMoveValues();
	virtual void updateCameraCords();
public:
	CameraFixed();
	CameraFixed(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	~CameraFixed();
	virtual void simulate(double);
	virtual void apply();
	void setKey(bool, bool, bool, bool, bool, bool);
};
#endif