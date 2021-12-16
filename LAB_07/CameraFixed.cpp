#include "Camera.h"
CameraFixed::CameraFixed() : Camera(){
	cameraPos = glm::vec3(0.0, 0.0, 0.0);
	cameraFront = glm::vec3(0.0, 0.0, 0.0);
	cameraUp = glm::vec3(0.0, 1.0, 0.0);
	setVectorAndMoveValues();
	updateCameraCords();
}
CameraFixed::CameraFixed(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat targetX, GLfloat targetY, GLfloat targetZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : Camera() {
	cameraPos = glm::vec3(posX, posY, posZ);
	cameraFront = glm::vec3(targetX, targetY, targetZ);
	cameraUp = glm::vec3(upX, upY, upZ);
	setVectorAndMoveValues();
	updateCameraCords();
}
CameraFixed::~CameraFixed() {
	
}
void CameraFixed::setKey(bool left, bool right, bool up, bool down, bool forward, bool backward) {
	moveLeft = left;
	moveRight = right;
	moveUp = up;
	moveDown = down;
	zoomIn = forward; 
	zoomOut = backward;
}
void CameraFixed::simulate(double sec) {
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
	yaw > 360.0 ? yaw = 0.0 + sec * speed :
		yaw < 0.0 ? yaw = 360.0 - sec * speed : 
		0;
	pitch > 89.0 ? pitch = 89.0 :
		pitch < -89.0 ? pitch = -89.0 : 
		0;
	radius < 1.0 ? radius = 1.0 :
		radius > 90.0 ? radius = 90.0 
		: 0;
	updateCameraCords();
}
void CameraFixed::apply() {
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, cameraFront.x, cameraFront.y, cameraFront.z, cameraUp.x, cameraUp.y, cameraUp.z);
}
void CameraFixed::updateCameraCords() {
	cameraPos.x = radius * cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	cameraPos.y = radius * sin(glm::radians(pitch));
	cameraPos.z = radius * cos(glm::radians(pitch)) * sin(glm::radians(yaw));
}
void CameraFixed::setVectorAndMoveValues() {
	radius = 15.0;
	pitch = 15.0;
	yaw = 7.5;
	speed = 90.0f;
	moveLeft = false;
	moveRight = false;
	moveUp = false;
	moveDown = false;
	zoomIn = false;
	zoomOut = false;
}