#include "Material.h"
PhongMaterial::PhongMaterial() : Material() {
	setAmbient(glm::vec4(1.0, 0.0, 0.0, 1.0));
	setDiffuse(glm::vec4(0.4, 0.0, 0.0, 1.0));
	setSpecular(glm::vec4(1.0, 1.0, 1.0, 1.0));
	setEmission(glm::vec4(0.0, 0.0, 0.0, 1.0));
	setShininess(64.0f);
}
PhongMaterial::PhongMaterial(glm::vec4 ambientColor, glm::vec4 diffuseColor, glm::vec4 specularColor, glm::vec4 emissionColor) : Material() {
	setAmbient(ambientColor);
	setDiffuse(diffuseColor);
	setSpecular(specularColor);
	setEmission(emissionColor);
	setShininess(0.0f);
}
PhongMaterial::PhongMaterial(glm::vec4 ambientColor, glm::vec4 diffuseColor, glm::vec4 specularColor, glm::vec4 emissionColor, GLfloat shininessValue) : Material() {
	setAmbient(ambientColor);
	setDiffuse(diffuseColor);
	setSpecular(specularColor);
	setEmission(emissionColor);
	setShininess(shininessValue);
}
PhongMaterial::PhongMaterial(const PhongMaterial& phmat) {
	ambient = phmat.ambient;
	diffuse = phmat.diffuse;
	specular = phmat.specular;
	emission = phmat.emission;
	shininess = phmat.shininess;
};
void PhongMaterial::apply() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(specular));
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(emission));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
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
void PhongMaterial::load(std::string fileNameFullPath) {
	std::ifstream lightData(fileNameFullPath.c_str(), std::ios_base::in);
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
				case lightConst::colorType::EMISSION: {
					setEmission(dataToVec::getVec4FromFile(lightData));
				} break;
				case lightConst::colorType::SHININESS: {
					lightData >> buffString;
					setShininess(stof(buffString));
				} break;
				}
			}
		}
		catch (std::exception e) {
			msg::error::outErrMessage(fileNameFullPath, msg::error::errType::FILE_BROKEN, e);
		}
	}
	else {
		msg::error::outErrMessage(fileNameFullPath, msg::error::errType::FILE_NOT_EXIST);
	}
	lightData.close();
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
	if (strData == lightConst::lightType[4])
		return lightConst::colorType::SHININESS;
	return static_cast<lightConst::colorType>(0);
};