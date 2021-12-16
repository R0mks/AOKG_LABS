#ifndef  LIGHT_H
#define  LIGHT_H
#include "projectGlobalConst.h"
#include <GL/freeglut.h>
#include <GLM/glm.hpp>
#include <string>
class Light
{
public:
	Light();
	Light(glm::vec4 position);
	void setPosition(glm::vec4);
	void setAmbient(glm::vec4);
	void setDiffuse(glm::vec4);
	void setSpecular(glm::vec4);
	void apply(GLenum LightNumber = GL_LIGHT0); 
	void load(std::string);
private:
	glm::vec4 position;
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	lightConst::colorType getStringCode(std::string const&);
};
#endif;