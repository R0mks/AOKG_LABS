#include "PhongMaterial.h"
#include "projectGlobalConstData.h"
#include <GL/freeglut.h>
#include <GL/GLU.h>
#include <GL/GL.h>
#include <string>
#include <iostream>
#include <fstream>
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>
PhongMaterial::PhongMaterial() {
	setAmbient(glm::vec4(1.0, 0.0, 0.0, 1.0));
	setDiffuse(glm::vec4(0.4, 0.0, 0.0, 1.0));
	setSpecular(glm::vec4(1.0, 1.0, 1.0, 1.0));
	setEmission(glm::vec4(0.0, 0.0, 0.0, 1.0));
	setShininess(64.0f);
}
void PhongMaterial::setAmbient(glm::vec4 ambientColor) {
	ambient = ambientColor;
}
void PhongMaterial::setDiffuse(glm::vec4 diffuseColor) {
	diffuse = diffuseColor;
}
void PhongMaterial::setSpecular(glm::vec4 specularColor) {
	specular = specularColor;
}
void PhongMaterial::setEmission(glm::vec4 emissionColor) {
	emission = emissionColor;
}
void PhongMaterial::setShininess(float p) {
	shininess = p;
}
void PhongMaterial::load(std::string filename) {
	std::ifstream lightData(filename.c_str(), std::ios_base::in);
	std::string buffString;
	if(lightData.is_open()){
		while (!lightData.eof()) {
			lightData >> buffString;
			switch (getStringCode(buffString)) {
			case lightConst::colorType::AMBIENT: {
				setAmbient(getVec4FromFile(lightData));
			}; break;
			case lightConst::colorType::DIFUSE: {
				setDiffuse(getVec4FromFile(lightData));
			}; break;
			case lightConst::colorType::SPECULAR: {
				setSpecular(getVec4FromFile(lightData));
			}; break;
			case lightConst::colorType::EMISSION: {
				setEmission(getVec4FromFile(lightData));
			} break;
			case lightConst::colorType::SHININESS: {
				lightData >> buffString;
				setShininess(stof(buffString));
			} break;
			}
		}
	}
	else {
		std::cout << "\nФайл " << filename << " не может быть открыт или создан! Проверьте правильность введёных данных!\n";
	}
	lightData.close();
}

void PhongMaterial::apply() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(specular));
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(emission));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

glm::vec4 PhongMaterial::getVec4FromFile(std::ifstream& file) {
	double buffDouble[4];
	for (int i = 0; i < 4; i++)
		file >> buffDouble[i];
	return glm::vec4(buffDouble[0], buffDouble[1], buffDouble[2], buffDouble[3]);
}

lightConst::colorType PhongMaterial::getStringCode(std::string const& strData) {
	if (strData == lightConst::lightType[0])
		return lightConst::colorType::AMBIENT;
	if (strData == lightConst::lightType[1])
		return lightConst::colorType::DIFUSE;
	if (strData == lightConst::lightType[2])
		return lightConst::colorType::SPECULAR;
	if (strData == lightConst::lightType[3])
		return lightConst::colorType::EMISSION;
	if(strData == lightConst::lightType[4])
		return lightConst::colorType::SHININESS;
	return static_cast<lightConst::colorType>(0);
};