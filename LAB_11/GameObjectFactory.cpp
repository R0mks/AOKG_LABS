#include "GameObjectFactory.h"
bool GameObjectFactory::loadData(std::string directoryPath, std::string propetiesPath) {
	std::string fullPath = directoryPath + propetiesPath;
	for (int i = 0; i < gameObjectConst::GameObjectsCount; i++)
		graphicDataIndexes.insert(std::pair<std::string, gameObjectConst::GameObjectType>(std::string(gameObjectConst::GameObjectNames[i]), static_cast<gameObjectConst::GameObjectType>(i)));
	std::ifstream fileData(fullPath.c_str(), std::ios::in);
	if (!fileData.is_open()) {
		msg::error::outErrMessage(fullPath, msg::error::errType::FILE_NOT_EXIST);
		return 0;
	}
	std::string jsonString;
	getline(fileData, jsonString, static_cast<char>(0));
	fileData.close();
	rapidjson::Document document;
	document.Parse(jsonString.c_str());
	if (document.GetParseError() != 0) {
		msg::error::outErrMessage(fullPath, msg::error::errType::FILE_BROKEN);
		return 0;
	}
	std::set<gameObjectConst::GameObjectType> materialsTemporaryLst;
	for (auto it = document.MemberBegin(); it != document.MemberEnd(); it++) {
		std::map<std::string, gameObjectConst::GameObjectType>::iterator graphicDataCurrentElement = graphicDataIndexes.find(it->name.GetString());
		if (graphicDataCurrentElement != graphicDataIndexes.end()) {
			auto materialsInserted = materialsTemporaryLst.insert(graphicDataCurrentElement->second);
			auto meshesInserted = meshes.insert(std::pair<gameObjectConst::GameObjectType, std::shared_ptr<Mesh>>(graphicDataCurrentElement->second, std::make_shared<Mesh>()));
			std::map<gameObjectConst::GameObjectType, std::shared_ptr<Mesh>>::iterator meshesIterator;
			if (it->value.HasMember("mesh") && meshesInserted.second) {
				meshesIterator = meshesInserted.first;
				if (it->value["mesh"].IsString())
					meshesIterator->second->load(directoryPath + "\\" + it->value["mesh"].GetString());
			}
			if (it->value.HasMember("material") && materialsInserted.second) {
				if (it->value["material"].HasMember("type")) {
					if (it->value["material"]["type"].IsString()) {
						std::string type = it->value["material"]["type"].GetString();
						if (type == "PhongMaterialWithTexture") {
							PhongMaterialWithTexture material;
							if (it->value["material"].HasMember("texture")) {
								if (it->value["material"]["texture"].IsString()) {
									std::shared_ptr<Texture> texture = std::make_shared<Texture>();
									texture->load(directoryPath + "\\" + it->value["material"]["texture"].GetString());
									material.setTexture(texture);
								}
							}
							if (it->value["material"].HasMember("ambient"))
								if (it->value["material"]["ambient"].IsArray())
									material.setAmbient(returnGlmVec4FromRapidjsonArray(it->value["material"]["ambient"].GetArray()));
							if (it->value["material"].HasMember("diffuse"))
								if (it->value["material"]["diffuse"].IsArray())
									material.setDiffuse(returnGlmVec4FromRapidjsonArray(it->value["material"]["diffuse"].GetArray()));
							if (it->value["material"].HasMember("specular"))
								if (it->value["material"]["specular"].IsArray())
									material.setSpecular(returnGlmVec4FromRapidjsonArray(it->value["material"]["specular"].GetArray()));
							if (it->value["material"].HasMember("emission"))
								if (it->value["material"]["emission"].IsArray())
									material.setEmission(returnGlmVec4FromRapidjsonArray(it->value["material"]["emission"].GetArray()));
							if (it->value["material"].HasMember("shininess"))
								if (it->value["material"]["shininess"].IsDouble())
									material.setShininess(it->value["material"]["shininess"].GetDouble());
								else if (it->value["material"]["shininess"].IsFloat())
									material.setShininess(it->value["material"]["shininess"].GetFloat());
							materials.insert(std::pair<gameObjectConst::GameObjectType, std::shared_ptr<PhongMaterialWithTexture>>(graphicDataCurrentElement->second, std::make_shared<PhongMaterialWithTexture>(material)));
						}
						else if (type == "PhongMaterial") {
							PhongMaterial material;
							if (it->value["material"].HasMember("ambient"))
								if (it->value["material"]["ambient"].IsArray())
									material.setAmbient(returnGlmVec4FromRapidjsonArray(it->value["material"]["ambient"].GetArray()));
							if (it->value["material"].HasMember("diffuse"))
								if (it->value["material"]["diffuse"].IsArray())
									material.setDiffuse(returnGlmVec4FromRapidjsonArray(it->value["material"]["diffuse"].GetArray()));
							if (it->value["material"].HasMember("specular"))
								if (it->value["material"]["specular"].IsArray())
									material.setSpecular(returnGlmVec4FromRapidjsonArray(it->value["material"]["specular"].GetArray()));
							if (it->value["material"].HasMember("emission"))
								if (it->value["material"]["emission"].IsArray())
									material.setEmission(returnGlmVec4FromRapidjsonArray(it->value["material"]["emission"].GetArray()));
							if (it->value["material"].HasMember("shininess"))
								if (it->value["material"]["shininess"].IsDouble())
									material.setShininess(it->value["material"]["shininess"].GetDouble());
								else if (it->value["material"]["shininess"].IsFloat())
									material.setShininess(it->value["material"]["shininess"].GetFloat());
							materials.insert(std::pair<gameObjectConst::GameObjectType, std::shared_ptr<PhongMaterial>>(graphicDataCurrentElement->second, std::make_shared<PhongMaterial>(material)));
						}
					}
				}
			}
		}
	}
	return 1;
}
glm::vec4 GameObjectFactory::returnGlmVec4FromRapidjsonArray(rapidjson::GenericArray<false, rapidjson::Value> data) {
	double tempArr[4] = { 0.0, 0.0, 0.0, 0.0 };
	int i = 0; 
	for (auto it = data.begin(); it != data.end() && i < 4; ++it, ++i)
		tempArr[i] = it->GetDouble();
	return glm::vec4(tempArr[0], tempArr[1], tempArr[2], tempArr[3]);
}
std::shared_ptr<GameObject> GameObjectFactory::create(gameObjectConst::GameObjectType type, int mapSize, float x, float y, float z) {
	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();
	GraphicObject graphicObject;
	auto meshesIterator = meshes.find(type);
	auto materialsIterator = materials.find(type);
	switch (type) {
	case gameObjectConst::GameObjectType::PLAYER: break;
	default: {
		graphicObject.setRotateAngle(glm::vec3(0.0, -90.0, 0.0));
		graphicObject.setSize(glm::vec3(-1.0, 1.0, 1.0));
	}; break;
	}
	graphicObject.setPosition(glm::vec3(x - mapSize / 2, y, z - mapSize / 2));
	if (type == gameObjectConst::GameObjectType::LIGHT_OBJECT
		|| type == gameObjectConst::GameObjectType::MONSTER
		|| type == gameObjectConst::GameObjectType::BOMB) {
		graphicObject.setRotateAngle(glm::vec3(0.0, 90.0, 0.0));
		graphicObject.setSize(glm::vec3(1.0, 1.0, -1.0));
	}
	if (meshesIterator != meshes.end())
		graphicObject.setMesh(meshesIterator->second);
	if(materialsIterator != materials.end())
		graphicObject.setLightMaterial(materialsIterator->second);
	gameObject->setGraphicObject(graphicObject);
	gameObject->setPosition(x, y, z);
	return gameObject;
}