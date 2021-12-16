#ifndef GAMEOBJECT_FACTORY_H
#define GAMEOBJECT_FACTORY_H
#include "GameObject.h";
#include "GraphicObject.h";
#include "projectGlobalConst.h"
#include "rapidjson/document.h"
#include <vector>
#include <string>
#include <map>
#include <fstream>
enum class GameObjectType {
	LIGHT_OBJECT = 0x00000001, HEAVY_OBJECT, BORDER_OBJECT, PLAYER, BOMB, MOSTER
};
class GameObjectFactory {
public:
	bool loadData(std::string directoryPath, std::string propetiesPath);
	std::shared_ptr<GameObject> create(GameObjectType type, int x, int y);
private:
	glm::vec4 returnGlmVec4FromRapidjsonArray(rapidjson::GenericArray<false, rapidjson::Value> data);
	std::map<GameObjectType, std::shared_ptr<Mesh>> meshes;
	std::map<GameObjectType, std::shared_ptr<PhongMaterial>> materials;
	std::map<std::string, GameObjectType> graphicDataIndexes;
};
#endif