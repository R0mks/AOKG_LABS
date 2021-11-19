#ifndef MOB_HEAD_EXAMPLE_H
#define MOB_HEAD_EXAMPLE_H
#include "GameObject.h"
#include "GraphicObject.h"
#include "projectGlobalConst.h"
#include <GL/freeglut.h>
#include <GL/GLU.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <map>
class MobHead{
public:
	MobHead();
	MobHead(int clrsCount, unsigned int mapSizeDegree, std::string mapFileFullPath, std::string meshFileFullPath, std::string clrsMaterialsDirectoryPath, std::map<unsigned char, std::string> materialsPattern, unsigned char emptyMaterialPattern);
	//explicit MobHead(int clrsCount, std::string meshFullFilePath, std::string clrsMaterialsPath, std::string* materialsNames, glm::vec3 position);
	//explicit MobHead(int clrsCount, std::string meshFullFilePath, std::string clrsMaterialsPath, std::string* materialsNames, int x, int y, int z);
	//explicit MobHead(int clrsCount, std::string meshFullFilePath, std::string clrsMaterialsPath, std::string* materialsNames, float x, float y, float z);
	~MobHead();
	void keyboardFunction(unsigned char key, void(*disabledFn)(unsigned char k, int x, int y));
	void draw(void);
	void loadMap(std::string fileNameFullPath);
	void loadMaterials();
	void loadMesh();
private:
	void generateHead(std::map<unsigned char, std::string>& materialsPattern, unsigned char& emptyMaterialPattern);
	int colorsCount, mapSize;
	std::vector<std::pair<bool,std::vector<GameObject>>> headParts;
	std::vector<std::shared_ptr<PhongMaterial>> materials;
	std::shared_ptr<Mesh> meshObject;
	GraphicObject* graphicObjects;
	std::string * materialsPaths;
	std::string meshPath;
	unsigned char *** map;
	glm::mat4 modelMatrix;
};
#endif