#include "Camera.h"
Camera::Camera(){
	cameraPos = glm::vec3(0.0, 0.0, 0.0);
	cameraFront = glm::vec3(0.0, 0.0, 0.0);
	cameraUp = glm::vec3(0.0, 1.0, 0.0);
	setVectorAndMoveValues();
}
Camera::~Camera() {

}
void Camera::simulate(double sec) {
	
}
void Camera::apply() {

}
void Camera::setVectorAndMoveValues() {
	radius = 0.0;
	pitch = 0.0;
	yaw = -90.0f;
}