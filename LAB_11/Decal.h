#ifndef DECAL_H
#define DECAL_H
#include <GL/glew.h>
#include <GLM/glm.hpp>

#include "Mesh.h"
#include "GraphicObject.h"
#include "Texture.h"
class Decal {
public:
	Decal(glm::vec2 position, int mapSize);
	static void init(std::string currentDirectoryPath);
	void setPosition(glm::vec2 position,int mapSize);
	glm::vec2 getPosition();
	void draw();
private:
	glm::vec2 position;
	GraphicObject graphicObject;
	static std::shared_ptr<PhongMaterialWithTexture> material;
	static std::shared_ptr<Mesh> mesh;
};
#endif