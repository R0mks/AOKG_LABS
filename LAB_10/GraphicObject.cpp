#include "GraphicObject.h"
GraphicObject::GraphicObject() {
	initGraphicObjectData(); 
	setPosition(glm::vec3(0, 0, 0));
	setAngle(0.0f);
	setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	setSize(glm::vec3(1.0f, 1.0f, 1.0f));
}
GraphicObject::GraphicObject(glm::vec3 pos, GLfloat ang, glm::vec3 color, glm::vec3 size) {
	initGraphicObjectData();
	setPosition(pos);
	setAngle(ang);
	setColor(color);
	setSize(size);
}
GraphicObject::~GraphicObject() {
	mesh.reset();
	material.reset();
}
void GraphicObject::initGraphicObjectData() {
	modelMatrix = glm::mat4(1.0f);
	material = nullptr;
	mesh = nullptr;
}
void GraphicObject::setPosition(glm::vec3 pos) {
	position = pos;
	modelMatrix = glm::translate(modelMatrix, position);
}
glm::vec3 GraphicObject::getPosition() {
	return position;
}
void GraphicObject::setAngle(GLfloat degreeValue) {
	angle = degreeValue;
	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
}
GLfloat GraphicObject::getAngle() {
	return angle;
}
void GraphicObject::setColor(glm::vec3 cl) {
	cl.x = cl.x > 1.0f ? 1.0f : cl.x < 0.0f ? 0.0f : cl.x;
	cl.y = cl.y > 1.0f ? 1.0f : cl.y < 0.0f ? 0.0f : cl.y;
	cl.z = cl.z > 1.0f ? 1.0f : cl.z < 0.0f ? 0.0f : cl.z;
	color.x = cl.x;
	color.y = cl.y;
	color.z = cl.z;
}
glm::vec3 GraphicObject::getColor() {
	return color;
}
void GraphicObject::setSize(glm::vec3 value = glm::vec3(1.0f, 1.0f, 1.0f)) {
	size = value.x == 0 || value.y == 0 || value.z  == 0 ? 
		glm::vec3(1.0f, 1.0f, 1.0f) : value;
	modelMatrix = glm::scale(modelMatrix, size);
}
glm::vec3 GraphicObject::getSize() {
	return size;
}
void GraphicObject::setLightMaterial(std::shared_ptr<Material> mt) {
	material = mt;
}
void GraphicObject::setMesh(std::shared_ptr<Mesh> msh) {
	mesh = msh;
}
void GraphicObject::draw(void) {
	glColor3f(color.x, color.y, color.z);
	if (material != nullptr)
		material->apply();
	glPushMatrix();
	glMultMatrixf(glm::value_ptr(modelMatrix));
	if (mesh != nullptr)
		mesh->draw();
	Texture::disableAll();
	glPopMatrix();
}
bool GraphicObject::operator!() const {
	return material == nullptr;
}
GraphicObject::operator bool() const {
	return material != nullptr;
}