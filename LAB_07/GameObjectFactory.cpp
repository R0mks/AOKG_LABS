#include "GameObjectFactory.h"
const int GameObjectsCount = 6;
const char* GameObjectNames[GameObjectsCount] = {
	"LightObject", "HeavyObject", "BorderObject", "Player", "Bomb", "Monster"
};
bool GameObjectFactory::loadData(std::string directoryPath, std::string propetiesPath) {
	std::string fullPath = directoryPath + propetiesPath;
	for (int i = 0; i < GameObjectsCount; i++)
		graphicDataIndexes.insert(std::pair<std::string, GameObjectType>(std::string(GameObjectNames[i]), static_cast<GameObjectType>(i+1)));
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
	for (auto it = document.MemberBegin(); it != document.MemberEnd(); it++) {
		std::map<std::string, GameObjectType>::iterator graphicDataCurrentElement = graphicDataIndexes.find(it->name.GetString());
		if (graphicDataCurrentElement != graphicDataIndexes.end()) {
			auto meshesInserted = meshes.insert(std::pair<GameObjectType, std::shared_ptr<Mesh>>(graphicDataCurrentElement->second, std::make_shared<Mesh>()));
			auto materialsInserted = materials.insert(std::pair<GameObjectType, std::shared_ptr<PhongMaterial>>(graphicDataCurrentElement->second, std::make_shared<PhongMaterial>()));
			std::map<GameObjectType, std::shared_ptr<Mesh>>::iterator meshesIterator;
			std::map<GameObjectType, std::shared_ptr<PhongMaterial>>::iterator materialsIterator;
			if (meshesInserted.second)
				meshesIterator = meshesInserted.first;
			if (materialsInserted.second)
				materialsIterator = materialsInserted.first;
			if (it->value.HasMember("mesh")) {
				if (it->value["mesh"].IsString())
					meshesIterator->second->load(directoryPath + "\\" + it->value["mesh"].GetString());
			}
			if (it->value.HasMember("material")) {
				if (it->value["material"].HasMember("ambient"))
					if (it->value["material"]["ambient"].IsArray())
						materialsIterator->second->setAmbient(returnGlmVec4FromRapidjsonArray(it->value["material"]["ambient"].GetArray()));
				if (it->value["material"].HasMember("diffuse"))
					if (it->value["material"]["diffuse"].IsArray())
						materialsIterator->second->setDiffuse(returnGlmVec4FromRapidjsonArray(it->value["material"]["diffuse"].GetArray()));
				if (it->value["material"].HasMember("specular"))
					if (it->value["material"]["specular"].IsArray())
						materialsIterator->second->setSpecular(returnGlmVec4FromRapidjsonArray(it->value["material"]["specular"].GetArray()));
				if (it->value["material"].HasMember("emission"))
					if (it->value["material"]["emission"].IsArray())
						materialsIterator->second->setEmission(returnGlmVec4FromRapidjsonArray(it->value["material"]["emission"].GetArray()));
				if (it->value["material"].HasMember("shininess"))
					if (it->value["material"]["shininess"].IsDouble())
						materialsIterator->second->setShininess(it->value["material"]["shininess"].GetDouble());
					else if (it->value["material"]["shininess"].IsFloat())
						materialsIterator->second->setShininess(it->value["material"]["shininess"].GetFloat());
			}
		}
	}
	return 1;
}
glm::vec4 GameObjectFactory::returnGlmVec4FromRapidjsonArray(rapidjson::GenericArray<false, rapidjson::Value> data) {
	double tempArr[4] = { 0.0, 0.0, 0.0, 0.0 };
	int i = 0;
	auto it = data.begin();
	for (; it != data.end() && i < 4; ++it, ++i)
		tempArr[i] = it->GetDouble();
	return glm::vec4(tempArr[0], tempArr[1], tempArr[2], tempArr[3]);
}
std::shared_ptr<GameObject> GameObjectFactory::create(GameObjectType type, int x, int y) {
	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();
	GraphicObject graphicObject;
	auto meshesIterator = meshes.find(type);
	auto materialsIterator = materials.find(type);
	if (meshesIterator != meshes.end())
		graphicObject.setMesh(meshesIterator->second);
	if(materialsIterator != materials.end())
		graphicObject.setLightMaterial(materialsIterator->second);
	gameObject->setGraphicObject(graphicObject);
	gameObject->setPosition(glm::vec2(x, y));
	return gameObject;
}