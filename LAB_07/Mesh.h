#ifndef  MESH_H
#define  MESH_H
//#include <GL/glew.h>
//#ifdef _WIN32
//#include <GL/wglew.h>
//#else
//#include <GL/glxew.h>
//#endif
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
	std::vector<meshConst::Vertex> vertices;
	std::vector<GLuint> indices;
	meshConst::modelTypeCode getStringCode(std::string const& strData);
	glm::ivec3 getPolygonDataFromFile(std::ifstream& file);
	glm::ivec3 getPolygonDataFromFile(std::istringstream& stringStream);
};
#endif