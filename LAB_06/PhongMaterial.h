#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H
#include <GLM/glm.hpp>
#include <string>
#include <fstream>
#include "projectGlobalConst.h"
class PhongMaterial
{
public:
	PhongMaterial();
	PhongMaterial(glm::vec4 ambientColor, glm::vec4 diffuseColor, glm::vec4 specularColor, glm::vec4 emissionColor);
	PhongMaterial(glm::vec4 ambientColor, glm::vec4 diffuseColor, glm::vec4 specularColor, glm::vec4 emissionColor, GLfloat shininessValue);
	void setAmbient(glm::vec4);
	void setDiffuse(glm::vec4);
	void setSpecular(glm::vec4);
	void setEmission(glm::vec4);
	void setShininess(float);
	void load(std::string fileNameFullPath);
	void apply();
private:
	lightConst::colorType getStringCode(std::string const& strData);
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	glm::vec4 emission;
	float shininess;
};
#endif