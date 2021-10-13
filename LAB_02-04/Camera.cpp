#include "Camera.h"
#include <iostream>
#include <GLM/glm.hpp>
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
		yaw += sec * speed;
	}
	if (moveRight) {
		yaw -= sec * speed;
	}
	if (moveUp) {
		pitch += sec * speed;
	}
	if (moveDown) {
		pitch -= sec * speed;
	}
	if (zoomIn) {
		radius -= sec * speed;
	}
	if (zoomOut) {
		radius += sec * speed;
	}
	pitch > 89.0 ? pitch = 89.0 :
		pitch < -89.0 ? pitch = -89.0 : 
		0;
	radius < 1.0 ? radius = 1.0 :
		radius > 90.0 ? radius = 90.0 
		: 0;
	updateCameraCords();
}
void Camera::apply() {
	gluLookAt(eyeX, eyeY, eyeZ, cenX, cenY, cenZ, upX, upY, upZ);
}
void Camera::updateCameraCords() {
	eyeX = radius * cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	eyeY = radius * sin(glm::radians(pitch));
	eyeZ = radius * cos(glm::radians(pitch)) * sin(glm::radians(yaw));
}
void Camera::setVectorAndMoveValues() {
	radius = eyeX;
	yaw = eyeY;
	pitch = eyeZ;
	moveLeft = false;
	moveRight = false;
	moveUp = false;
	moveDown = false;
	zoomIn = false;
	zoomOut = false;
}