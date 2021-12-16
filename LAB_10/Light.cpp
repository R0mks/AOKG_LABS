#include "Light.h"
#include "globalFunctions.h"
#include <fstream>
#include <iostream>
#include <GLM/gtc/type_ptr.hpp>
Light::Light() {
	setPosition(glm::vec4(15.0, 15.0, 7.5, 0.0));
	setAmbient(glm::vec4(1.0, 1.0, 1.0, 1.0));
	setDiffuse(glm::vec4(1.0, 1.0, 1.0, 1.0));
	setSpecular(glm::vec4(1.0, 1.0, 1.0, 1.0));
};
Light::Light(glm::vec4 position) {
	setPosition(position);
	setAmbient(glm::vec4(1.0, 1.0, 1.0, 1.0));
	setDiffuse(glm::vec4(1.0, 1.0, 1.0, 1.0));
	setSpecular(glm::vec4(1.0, 1.0, 1.0, 1.0));
};
void Light::setPosition(glm::vec4 pos) {
	position = pos;
};
void Light::setAmbient(glm::vec4 color) {
	ambient = color;
};
void Light::setDiffuse(glm::vec4 color) {
	diffuse = color;
};
void Light::setSpecular(glm::vec4 color) {
	specular = color;
};
void Light::apply(GLenum LightNumber) {
	glLightfv(LightNumber, GL_POSITION, glm::value_ptr(position));
	glLightfv(LightNumber, GL_AMBIENT, glm::value_ptr(ambient));
	glLightfv(LightNumber, GL_DIFFUSE, glm::value_ptr(diffuse));
	glLightfv(LightNumber, GL_SPECULAR, glm::value_ptr(specular));
	glEnable(LightNumber);
};
void Light::load(std::string filename) {
	std::ifstream lightData(filename.c_str(), std::ios_base::in);
	std::string buffString;
	if (lightData.is_open()) {
		lightData.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			while (!lightData.eof()) {
				lightData >> buffString;
				switch (getStringCode(buffString)) {
				case lightConst::colorType::AMBIENT: {
					setAmbient(dataToVec::getVec4FromFile(lightData));
				}; break;
				case lightConst::colorType::DIFUSE: {
					setDiffuse(dataToVec::getVec4FromFile(lightData));
				}; break;
				case lightConst::colorType::SPECULAR: {
					setSpecular(dataToVec::getVec4FromFile(lightData));
				}; break;
				case lightConst::colorType::POSITION: {
					setPosition(dataToVec::getVec4FromFile(lightData));
				}; break;
				}
			}
		}
		catch (std::exception e) {
			msg::error::outErrMessage(filename, msg::error::errType::FILE_BROKEN, e);
		}
	}
	else {
		msg::error::outErrMessage(filename, msg::error::errType::FILE_NOT_EXIST);
	}
	lightData.close();
}

lightConst::colorType Light::getStringCode(std::string const& strData) {
	if (strData == lightConst::lightType[0])
		return lightConst::colorType::AMBIENT;
	if (strData == lightConst::lightType[1])
		return lightConst::colorType::DIFUSE;
	if (strData == lightConst::lightType[2])
		return lightConst::colorType::SPECULAR;
	if (strData == lightConst::lightType[5])
		return lightConst::colorType::POSITION;
	return static_cast<lightConst::colorType>(0);
};