#ifndef GRAPHICOBJECT_H
#define GRAPHICOBJECT_H
#include <iostream>

#include <GL/glew.h>
#include "Material.h"
#include "Mesh.h"

#include <GL/freeglut.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/matrix_transform_2d.hpp>
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>

class GraphicObject {
public:
	GraphicObject();
	GraphicObject(glm::vec3 pos, glm::vec3 rotateAng, glm::vec3 color, glm::vec3 size = glm::vec3(1.0,1.0,1.0));
	~GraphicObject();
	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();
	void setRotateAngle(glm::vec3 rotate);
	glm::vec3 getRotateAngle();
	void setColor(glm::vec3 color);
	glm::vec3 getColor();
	void setSize(glm::vec3 size);
	glm::vec3 getSize();
	void setLightMaterial(std::shared_ptr<Material> materialptr);
	void setMesh(std::shared_ptr<Mesh> meshptr);
	void draw(void);
	bool operator !() const;
	operator bool() const;
private:
	glm::vec3 position;
	glm::vec3 color;
	glm::mat4 modelMatrix;
	glm::vec3 size;
	glm::vec3 angle;
	std::shared_ptr<Material> material;
	std::shared_ptr<Mesh> mesh;
	void initGraphicObjectData();
};
#endif