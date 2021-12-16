#ifndef GAMEOBJECT_FACTORY_H
#define GAMEOBJECT_FACTORY_H
#include <GL/glew.h>
#include "projectGlobalConst.h"
#include "Material.h"
#include "Mesh.h"
#include "Texture.h"
#include "GameObject.h";
#include "GraphicObject.h";
#include "projectGlobalConst.h"
#include "rapidjson/document.h"

#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
class GameObjectFactory {
public:
	bool loadData(std::string directoryPath, std::string propetiesPath);
	std::shared_ptr<GameObject> create(gameObjectConst::GameObjectType type, int mapSize, float x, float y, float z);
private:
	//inline void setLightMaterials(rapidjson::GenericMemberIterator<false, rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>> it, std::map<gameObjectConst::GameObjectType, std::shared_ptr<Material>>::iterator & materialsIterator, std::string materialType);
	glm::vec4 returnGlmVec4FromRapidjsonArray(rapidjson::GenericArray<false, rapidjson::Value> data);
	std::map<gameObjectConst::GameObjectType, std::shared_ptr<Mesh>> meshes;
	std::map<gameObjectConst::GameObjectType, std::shared_ptr<Material>> materials;
	std::map<std::string, gameObjectConst::GameObjectType> graphicDataIndexes;
};
#endif