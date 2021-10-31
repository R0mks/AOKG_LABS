#ifndef  GRAPHICOBJECT_H
#define  GRAPHICOBJECT_H
#include <windows.h>
#include <GL/freeglut.h>
#include <GLM/glm.hpp>
#include "PhongMaterial.h"
class GObject {
private:
	glm::vec3 position;
	glm::vec3 color;
	GLfloat angle;
	GLfloat size;
	std::shared_ptr<PhongMaterial> material;
public:
	GObject();
	GObject(glm::vec3 pos, GLfloat ang, glm::vec3 color, GLfloat size = 1.0f);
	void setPosition(glm::vec3);
	glm::vec3 getPosition();
	void setAngle(GLfloat);
	GLfloat getAngle();
	void setColor(glm::vec3);
	glm::vec3 getColor();
	void setSize(GLfloat);
	GLfloat getSize();
	void setLightMaterial(std::shared_ptr<PhongMaterial>);
	void draw(void);
};
#endif