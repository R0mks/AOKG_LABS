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
public:
	GLfloat speed;
	Camera();
	~Camera();
	virtual void simulate(double sec) = 0;
	virtual void apply() = 0;
};
class CameraFree : protected Camera{
private:
	float lastX, lastY;
	bool moveForward, moveBack, 
		moveLeft, moveRight;
	bool firstMouse;
	virtual void setVectorAndMoveValues();
public:
	GLfloat sensivity = 0.05f;
	CameraFree();
	CameraFree(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLfloat targetX, GLfloat targetY, GLfloat targetZ, GLfloat upX, GLfloat upY, GLfloat upZ);
	~CameraFree();
	virtual void simulate(double sec);
	virtual void apply();
	void setKey(bool forward, bool fallback, bool left, bool right);
	void mouseCallback(int x, int y);
	void mouseCallbackSaveLastXY(int button, int state, int x, int y);
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
	void updateCameraCords();
public:
	CameraFixed();
	CameraFixed(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat targetX, GLfloat targetY, GLfloat targetZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);
	~CameraFixed();
	virtual void simulate(double sec);
	virtual void apply();
	void setKey(bool left, bool right, bool up, bool down, bool forward, bool backward);
};
#endif