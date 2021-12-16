#include "GameObject.h"
GameObject::GameObject() {
	setPosition(glm::vec3(0, 0, 0));
	setGameObjectsDefaults();
};
GameObject::GameObject(glm::vec2 pos) {
	setPosition(pos);
	setGameObjectsDefaults();
};
GameObject::GameObject(glm::vec3 pos) {
	setPosition(pos);
	setGameObjectsDefaults();
};
GameObject::GameObject(int x, int y) {
	setPosition(x, y);
	setGameObjectsDefaults();
};
GameObject::GameObject(int x, int y, int z) {
	setPosition(x, y, z);
	setGameObjectsDefaults();
};
GameObject::GameObject(float x, float y, float z) {
	setPosition(x, y, z);
	setGameObjectsDefaults();
};
void GameObject::setGameObjectsDefaults(GLfloat speedValue) {
	progress = 0.0f;
	movingState = gameObjectConst::MoveDirectionState::STOP;
	prevState = gameObjectConst::MoveDirectionState::STOP;
	speed = speedValue;
}
void GameObject::setGraphicObject(const GraphicObject& graphicObj) {
	graphicObject = graphicObj;
};
void GameObject::setPosition(glm::vec2 pos) {
	position = glm::vec3(pos.x, 0.0, pos.y);
};
void GameObject::setPosition(glm::vec3 pos) {
	position = pos;
};
void GameObject::setPosition(int x, int y) {
	int z = position.y != NULL ? position.y : 0.0;
	position = glm::vec3(x, z, y);
};
void GameObject::setPosition(int x, int y, int z) {
	position = glm::vec3(x, y, z);
};
void GameObject::setPosition(float x, float y) {
	float z = position.y != NULL ? position.y : 0.0;
	position = glm::vec3(x, y, z);
};
void GameObject::setPosition(float x, float y, float z) {
	position = glm::vec3(x, y, z);
};
glm::vec2 GameObject::getPosition2d() {
	return glm::vec2(position.x, position.z);
};
glm::vec3 GameObject::getPosition3d() {
	return position;
}
glm::vec3 GameObject::getGraphicPosition() {
	return graphicObject.getPosition();
};



void GameObject::move(gameObjectConst::MoveDirectionState direction, GLfloat speedValue) {
	if (!isMoving()) {
		movingState = direction;
		speed = speedValue;
	}
};
bool GameObject::isMoving() {
	return  movingState != gameObjectConst::MoveDirectionState::STOP  ? true : false;
};
bool GameObject::isMovingDone() {
	return progress == 1.0 ? true : false;
}
void GameObject::setPrevState(gameObjectConst::MoveDirectionState dir) {
	prevState = dir;
};
gameObjectConst::MoveDirectionState GameObject::getPrevState() {
	return prevState;
};
void GameObject::simulate(GLfloat sec) {
	if (isMoving()) {
		GLfloat distance = progress + (sec * speed) <= 1.0 ? 
			sec * speed : 1.0 - progress;
		progress + (sec * speed) <= 1.0 ?
			progress += (sec * speed) : progress = 1.0;
		switch (movingState) {
		case gameObjectConst::MoveDirectionState::UP: {
			graphicObject.setPosition(glm::vec3(0, 0, distance));
		}; break;
		case gameObjectConst::MoveDirectionState::DOWN: {
			graphicObject.setPosition(glm::vec3(0, 0, -distance));
		}; break;
		case gameObjectConst::MoveDirectionState::LEFT: {
			graphicObject.setPosition(glm::vec3(distance, 0, 0));
		}; break;
		case gameObjectConst::MoveDirectionState::RIGHT: {
			graphicObject.setPosition(glm::vec3(-distance, 0, 0));
		}; break;
		}
	}
	if(isMovingDone()) {
		glm::vec3 newPosition = getPosition3d();
		glm::vec3 graphicObjectPosition = graphicObject.getPosition();
		switch (movingState) {
		case gameObjectConst::MoveDirectionState::UP: {
			setPosition(glm::vec3(newPosition.x - 1, newPosition.y, newPosition.z));
		}; break;
		case gameObjectConst::MoveDirectionState::DOWN: {
			setPosition(glm::vec3(newPosition.x + 1, newPosition.y, newPosition.z));
		}; break;
		case gameObjectConst::MoveDirectionState::LEFT: {
			setPosition(glm::vec3(newPosition.x, newPosition.y, newPosition.z - 1));
		}; break;
		case gameObjectConst::MoveDirectionState::RIGHT: {
			setPosition(glm::vec3(newPosition.x, newPosition.y, newPosition.z + 1));
		}; break;
		}
		movingState = gameObjectConst::MoveDirectionState::STOP;
		progress = 0.0;
	}

};
void GameObject::draw(void) {
	graphicObject.draw();
};