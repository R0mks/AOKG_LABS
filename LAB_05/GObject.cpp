#include "GObject.h"
#include <GLM/glm.hpp>
#include "PhongMaterial.h"
#include <iostream>
GObject::GObject() { 
	setPosition(glm::vec3(0, 0, 0));
	setAngle(0.0f);
	setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	setSize(1.0f);
}
GObject::GObject(glm::vec3 pos, GLfloat ang, glm::vec3 color, GLfloat size) {
	setPosition(pos);
	setAngle(ang);
	setColor(color);
	setSize(size);
}
void GObject::setPosition(glm::vec3 pos) {
	position = pos;
}
glm::vec3 GObject::getPosition() {
	return position;
}
void GObject::setAngle(GLfloat degreeValue) {
	angle = degreeValue;
}
GLfloat GObject::getAngle() {
	return angle;
}
void GObject::setColor(glm::vec3 cl) {
	cl.x = cl.x > 1.0f ? 1.0f : cl.x < 0.0f ? 0.0f : cl.x;
	cl.y = cl.y > 1.0f ? 1.0f : cl.y < 0.0f ? 0.0f : cl.y;
	cl.z = cl.z > 1.0f ? 1.0f : cl.z < 0.0f ? 0.0f : cl.z;
	color.x = cl.x;
	color.y = cl.y;
	color.z = cl.z;
}
glm::vec3 GObject::getColor() {
	return color;
}
void GObject::setSize(GLfloat value = 1.0f) {
	size = value <= 0 ? 1.0f : value;
}
GLfloat GObject::getSize() {
	return size;
}
void GObject::setLightMaterial(std::shared_ptr<PhongMaterial> mt) {
	material = mt;
}
void GObject::draw(void) {
	glColor3f(color.x, color.y, color.z);
	if (material != nullptr)
		material->apply();
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glutSolidTeapot(size);
	glPopMatrix();
}