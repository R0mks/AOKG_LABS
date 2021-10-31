#include "Camera.h"
#include <iostream>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
CameraFree::CameraFree() : Camera(){
	cameraPos = glm::vec3(0.0, 0.0, 0.0);
	cameraFront = glm::vec3(0.0, 0.0, -1.0);
	cameraUp = glm::vec3(0.0, 1.0, 0.0);
	setVectorAndMoveValues();
}
CameraFree::CameraFree(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat targetX, GLfloat targetY, GLfloat targetZ, GLfloat upX, GLfloat upY, GLfloat upZ) : Camera(){
	cameraPos = glm::vec3(posX, posY, posZ);
	cameraFront = glm::vec3(targetX, targetY, targetZ);
	cameraUp = glm::vec3(upX, upY, upZ);
	setVectorAndMoveValues();
}
CameraFree::~CameraFree() {

}
void CameraFree::setKey(bool forward, bool fallback, bool left, bool right) {
	moveForward = forward;
	moveBack = fallback;
	moveLeft = left;
	moveRight = right;
}
void CameraFree::mouseCallback(int xpos, int ypos) {
	if (isFirstMouse()) {
		lastX = xpos;
		lastY = ypos;
		setFirstMouse();
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	xoffset *= sensivity;
	yoffset *= sensivity;
	yaw += xoffset;
	pitch += yoffset;
	pitch > 89.0 ? pitch = 89.0 :
		pitch < -89.0 ? pitch = -89.0 :
		0;
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}
void CameraFree::mouseCallbackSaveLastXY(int button, int state, int x, int y) {
	lastX = x;
	lastY = y;
}
void CameraFree::simulate(double sec) {
	float deltaSpeed = speed * sec;
	if (moveForward) {
		cameraPos += deltaSpeed * cameraFront;
	}
	if (moveBack) {
		cameraPos -= deltaSpeed * cameraFront;
	}
	if (moveLeft) {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * deltaSpeed;
	}
	if (moveRight) {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * deltaSpeed;
	}
	updateCameraCords();
}
void CameraFree::getLastXYForCamera(){
	lastX = glutGet(GLUT_SCREEN_WIDTH) / 2;
	lastY = glutGet(GLUT_SCREEN_HEIGHT) / 2;
}
void CameraFree::apply(){
	glm::vec3 newFront = cameraFront + cameraPos;
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, newFront.x, newFront.y, newFront.z, cameraUp.x, cameraUp.y, cameraUp.z);
}
inline bool CameraFree::isFirstMouse() {
	return firstMouse;
}
inline void CameraFree::setFirstMouse() {
	if (firstMouse == true) firstMouse = false;
}
void CameraFree::gotoCenter() {
	cameraPos = glm::vec3(0.0, 0.0, 0.0);
	cameraFront = glm::vec3(0.0, 0.0, -1.0);
	cameraUp = glm::vec3(0.0, 1.0, 0.0);
	yaw = -90.0;
	pitch = 0.0;
}
void CameraFree::updateCameraCords() {
	cameraPos = glm::vec3(cameraPos.x, cameraPos.y, cameraPos.z);
	cameraFront = glm::vec3(cameraFront.x, cameraFront.y, cameraFront.z);
	cameraUp = glm::vec3(cameraUp.x, cameraUp.y, cameraUp.z);
}
void CameraFree::setVectorAndMoveValues() {
	yaw = -90.0;
	pitch = 0.0;
	speed = 30.0f;
	firstMouse = true;
	moveLeft = false;
	moveRight = false;
	moveForward = false;
	moveBack = false;
}
