#ifndef  GAMEOBJECT_H
#define  GAMEOBJECT_H
#include <GL/glew.h>
#include "projectGlobalConst.h"
#include "GraphicObject.h"
#include <GLM/glm.hpp>
class GameObject {
public:
	GameObject();
	GameObject(glm::vec2 pos);
	GameObject(glm::vec3 pos);
	GameObject(int x, int y);
	GameObject(int x, int y, int z);
	GameObject(float x, float y, float z);
	void setPosition(glm::vec2 position);
	void setPosition(glm::vec3 position);
	void setPosition(int x, int y);
	void setPosition(int x, int y, int z);
	void setPosition(float x, float y);
	void setPosition(float x, float y, float z);
	glm::vec2 getPosition2d();
	glm::vec3 getPosition3d();
	glm::vec3 getGraphicPosition();
	void setGraphicObject(const GraphicObject& graphicObject);
	void move(gameObjectConst::MoveDirectionState direction, GLfloat speed = 3.0f);
	bool isMoving();
	bool isMovingDone();
	void simulate(GLfloat sec);
	void draw(void);
protected:
	glm::vec3 position;
private:
	void setGameObjectsDefaults(GLfloat speedValue = 3.0f);
	GraphicObject graphicObject;
	gameObjectConst::MoveDirectionState movingState;
	GLfloat progress;
	GLfloat speed;
};
#endif