#ifndef PROJECTGLOBALCONST_H
#define PROJECTGLOBALCONST_H
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <GL/freeglut.h>
#include <string>
#include <iostream>
#include <vector>
namespace lightConst {
	enum class colorType {
		NULLCLR = 0, AMBIENT, DIFUSE, SPECULAR, EMISSION, SHININESS, POSITION
	};
	extern const char* lightType[6];
	extern const char* phongMaterialExtension;
}
namespace meshConst {
	struct Vertex {
		glm::vec3 coordinates;
		glm::vec3 textureCoordinates;
		glm::vec3 normalCoordinates;
		Vertex(glm::vec3 coordinatesVector, glm::vec3 textureVector, glm::vec3 normalVector) {
			coordinates = coordinatesVector;
			textureCoordinates = textureVector;
			normalCoordinates = normalVector;
		}
	};
	enum class modelTypeCode {
		NULLPTN = 0, VERTICE, NORMALE, TEXTURE, POLYGON
	};
	extern const char* modelType[4];
	extern const char* modelExtension;
}
namespace gameObjectConst {
	enum class MoveDirectionState {
		STOP = 0x00, LEFT, RIGHT, UP, DOWN
	};
	enum class GameObjectType {
		EMPTY = 0x0000, LIGHT_OBJECT, HEAVY_OBJECT, BORDER_OBJECT, PLAYER, BOMB, MOSTER
	};
	constexpr int GameObjectsCount = 7;
	extern const char* GameObjectNames[GameObjectsCount];
}
namespace msg {
	namespace error {
		enum class errType {
			FILE_OK = 0, FILE_BROKEN, FILE_NOT_EXIST 
		};
		extern const char* fileFirstPartTemplate;
		extern const char* fileErrListMessageTemplates[2];
		extern void outErrMessage(std::string &name, errType num);
		extern void outErrMessage(std::string &name, errType num, std::exception &exception);
	}
}
#endif
