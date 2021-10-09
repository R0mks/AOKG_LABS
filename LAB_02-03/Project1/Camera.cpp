#include "Camera.h"
#include <iostream>

Camera::Camera() {
	eyeX = 15.0; eyeY = 15.0; eyeZ = 7.5;
	cenX = 0.0; cenY = 0.0; cenZ = 0.0;
	upX = 0.0; upY = 1.0; upZ = 0.0;
	setVectorAndMoveValues();
}
Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat targetX, GLfloat targetY, GLfloat targetZ, GLfloat upX, GLfloat upY, GLfloat upZ){
	eyeX = posX; eyeY = posY; eyeZ = posZ;
	cenX = targetX; cenY = targetY; cenZ = targetZ;
	Camera::upX = upX; Camera::upY = upY; Camera::upZ = upZ;
	setVectorAndMoveValues();
}
Camera::~Camera(void) {
	
}

void Camera::setKey(bool left, bool right, bool up, bool down, bool forward, bool backward) {
	moveLeft = left;
	moveRight = right;
	moveUp = up;
	moveDown = down;
	zoomIn = forward; 
	zoomOut = backward;
}
void Camera::simulate(double sec) {
	if (moveLeft) {

	}
	if (moveRight) {

	}
	if (moveUp) {

	}
	if (moveDown) {

	}
	if (zoomIn) {

	}
	if (zoomOut) {

	}
}
void Camera::apply() {
	gluLookAt(eyeX, eyeY, eyeZ, cenX, cenY, cenZ, upX, upY, upZ);
}

void Camera::setVectorAndMoveValues() {
	moveLeft = false;
	moveRight = false;
	moveUp = false;
	moveDown = false;
	zoomIn = false;
	zoomOut = false;
}