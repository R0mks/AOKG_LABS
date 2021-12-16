#ifndef  MESH_H
#define  MESH_H
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/GLU.h>
#include <GLM/glm.hpp>

#include <vector>
#include <string>
#include <map>
#include "projectGlobalConst.h"
class Mesh {
public:
	Mesh();
	~Mesh();
	void load(std::string fileNameFullPath);
	void draw();
private:
	int indicesCount;
	GLuint verticesBufferId, indicesBufferId;
	meshConst::modelTypeCode getStringCode(std::string const& strData);
	glm::ivec3 getPolygonDataFromFile(std::ifstream& file);
	glm::ivec3 getPolygonDataFromFile(std::istringstream& stringStream);
};
#endif