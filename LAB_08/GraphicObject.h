#ifndef GRAPHICOBJECT_H
#define  GRAPHICOBJECT_H
#include <windows.h>

#include <GL/glew.h>
#include "PhongMaterial.h"
#include "Mesh.h"
#include <GL/freeglut.h>

#include <GLM/glm.hpp>
#include <GLM/gtx/matrix_transform_2d.hpp>
class GraphicObject {
private:
	glm::vec3 position;
	glm::vec3 color;
	glm::mat4 modelMatrix;
	glm::vec3 size;
	GLfloat angle;
	std::shared_ptr<PhongMaterial> material;
	std::shared_ptr<Mesh> mesh;
	void initGraphicObjectData();
public:
	GraphicObject();
	GraphicObject(glm::vec3 pos, GLfloat ang, glm::vec3 color, glm::vec3 size = glm::vec3(1.0,1.0,1.0));
	~GraphicObject();
	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();
	void setAngle(GLfloat angle);
	GLfloat getAngle();
	void setColor(glm::vec3 color);
	glm::vec3 getColor();
	void setSize(glm::vec3 size);
	glm::vec3 getSize();
	void setLightMaterial(std::shared_ptr<PhongMaterial> materialptr);
	void setMesh(std::shared_ptr<Mesh> meshptr);
	void draw(void);
	bool operator !() const;
	operator bool() const;
};
#endif