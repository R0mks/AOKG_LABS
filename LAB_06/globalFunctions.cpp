#include "globalFunctions.h"
namespace dataToVec {
	glm::vec2 getVec2FromFile(std::ifstream& file) {
		double buffDouble[2];
		for (int i = 0; i < 2; i++)
			file >> buffDouble[i];
		return glm::vec2(buffDouble[0], buffDouble[1]);
	}
	glm::vec2 getVec2FromFile(std::istringstream& line) {
		double buffDouble[2];
		for (int i = 0; i < 2; i++)
			line >> buffDouble[i];
		return glm::vec2(buffDouble[0], buffDouble[1]);
	}
	glm::vec3 getVec3FromFile(std::ifstream& file) {
		double buffDouble[3];
		for (int i = 0; i < 3; i++)
			file >> buffDouble[i];
		return glm::vec3(buffDouble[0], buffDouble[1], buffDouble[2]);
	}
	glm::vec3 getVec3FromFile(std::istringstream& line) {
		double buffDouble[3];
		for (int i = 0; i < 3; i++)
			line >> buffDouble[i];
		return glm::vec3(buffDouble[0], buffDouble[1], buffDouble[2]);
	}
	glm::vec4 getVec4FromFile(std::ifstream& file) {
		double buffDouble[4];
		for (int i = 0; i < 4; i++)
			file >> buffDouble[i];
		return glm::vec4(buffDouble[0], buffDouble[1], buffDouble[2], buffDouble[3]);
	}
	glm::vec4 getVec4FromFile(std::istringstream& line) {
		double buffDouble[4];
		for (int i = 0; i < 4; i++)
			line >> buffDouble[i];
		return glm::vec4(buffDouble[0], buffDouble[1], buffDouble[2], buffDouble[3]);
	}
}