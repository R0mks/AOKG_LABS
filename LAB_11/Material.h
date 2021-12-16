#ifndef	 MATERIAL_H
#define  MATERIAL_H
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include <string>
#include <fstream>

#include "projectGlobalConst.h"
#include "globalFunctions.h"
#include "Texture.h"

class Material {
public:
	Material();
	virtual void apply() = 0;
};
class PhongMaterial : public Material {
public:
	PhongMaterial();
	PhongMaterial(glm::vec4 ambientColor, glm::vec4 diffuseColor, glm::vec4 specularColor, glm::vec4 emissionColor);
	PhongMaterial(glm::vec4 ambientColor, glm::vec4 diffuseColor, glm::vec4 specularColor, glm::vec4 emissionColor, GLfloat shininessValue);
	PhongMaterial(const PhongMaterial& phmat);
	void setAmbient(glm::vec4);
	void setDiffuse(glm::vec4);
	void setSpecular(glm::vec4);
	void setEmission(glm::vec4);
	void setShininess(float);
	void load(std::string fileNameFullPath);
	virtual void apply();
private:
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	glm::vec4 emission;
	float shininess;
	lightConst::colorType getStringCode(std::string const& strData);
};
class PhongMaterialWithTexture : public Material {
public:
	PhongMaterialWithTexture();
	PhongMaterialWithTexture(glm::vec4 ambientColor, glm::vec4 diffuseColor, glm::vec4 specularColor, glm::vec4 emissionColor);
	PhongMaterialWithTexture(glm::vec4 ambientColor, glm::vec4 diffuseColor, glm::vec4 specularColor, glm::vec4 emissionColor, GLfloat shininessValue);
	PhongMaterialWithTexture(const PhongMaterialWithTexture& phmat);
	~PhongMaterialWithTexture();
	void setAmbient(glm::vec4);
	void setDiffuse(glm::vec4);
	void setSpecular(glm::vec4);
	void setEmission(glm::vec4);
	void setShininess(float);
	void load(std::string fileNameFullPath);
	virtual void apply();
	void setTexture(std::shared_ptr<Texture> texture);
private:
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	glm::vec4 emission;
	float shininess;
	std::shared_ptr<Texture> texture;
	lightConst::colorType getStringCode(std::string const& strData);
};
#endif