#include "GameObject.h"
GameObject::GameObject() {
	setPosition(glm::vec3(0, 0, 0));
};
GameObject::GameObject(glm::vec2 pos) {
	setPosition(pos);
};
GameObject::GameObject(glm::vec3 pos) {
	setPosition(pos);
};
GameObject::GameObject(int x, int y) {
	setPosition(x, y);
};
GameObject::GameObject(int x, int y, int z) {
	setPosition(x, y, z);
};
GameObject::GameObject(float x, float y, float z) {
	setPosition(x, y, z);
};
void GameObject::setGraphicObject(const GraphicObject& graphicObj) {
	graphicObject = graphicObj;
};
void GameObject::setPosition(glm::vec2 pos) {
	position = glm::vec3(pos, 0.0);
	if(graphicObject)
		graphicObject.setPosition(glm::vec3(position.x, 0.0f, position.y));
};
void GameObject::setPosition(glm::vec3 pos) {
	position = pos;
	if(graphicObject)
		graphicObject.setPosition(position);
};
void GameObject::setPosition(int x, int y) {
	position = glm::vec3(glm::vec2(x, y), 0.0);
	if (graphicObject)
		graphicObject.setPosition(position);
};
void GameObject::setPosition(int x, int y, int z) {
	position = glm::vec3(x, y, z);
	if (graphicObject)
		graphicObject.setPosition(position);
};
void GameObject::setPosition(float x, float y) {
	position = glm::vec3(glm::vec2(x, y), 0.0);
	if (graphicObject)
		graphicObject.setPosition(position);
};
void GameObject::setPosition(float x, float y, float z) {
	position = glm::vec3(x, y, z);
	if (graphicObject)
		graphicObject.setPosition(position);
};
glm::vec2 GameObject::getPosition2d() {
	return glm::vec2(position.x, position.y);
};
glm::vec3 GameObject::getPosition3d() {
	return position;
}
glm::vec3 GameObject::getGraphicPosition() {
	return graphicObject.getPosition();
};
void GameObject::draw(void) {
	graphicObject.draw();
};