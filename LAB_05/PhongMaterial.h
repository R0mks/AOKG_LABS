#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H
#include <GLM/glm.hpp>
#include <string>
#include <fstream>
#include "projectGlobalConstData.h"
class PhongMaterial
{
public:
	PhongMaterial();
	void setAmbient(glm::vec4);
	void setDiffuse(glm::vec4);
	void setSpecular(glm::vec4);
	void setEmission(glm::vec4);
	void setShininess(float);
	void load(std::string);
	void apply();
private:
	lightConst::colorType getStringCode(std::string const&);
	glm::vec4 getVec4FromFile(std::ifstream&);
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	glm::vec4 emission;
	float shininess;
};
#endif