#ifndef GLOBAL_FNS_H
#define GLOBAL_FNS_H
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <map>
#include <fstream>
#include <sstream>
#include "GraphicObject.h"
#include "GameObject.h"
namespace dataToVec {
	extern glm::vec2 getVec2FromFile(std::ifstream& file);
	extern glm::vec3 getVec3FromFile(std::ifstream& file);
	extern glm::vec4 getVec4FromFile(std::ifstream& file);
	extern glm::vec2 getVec2FromFile(std::istringstream& line);
	extern glm::vec3 getVec3FromFile(std::istringstream& line);
	extern glm::vec4 getVec4FromFile(std::istringstream& line);
}
#endif
