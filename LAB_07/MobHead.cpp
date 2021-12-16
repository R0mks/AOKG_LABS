#include "MobHead.h";
MobHead::MobHead() {
	colorsCount = 0;
	materialsPaths = nullptr;
	graphicObjects = nullptr;
	meshObject = nullptr;
	mapSize = 0;
	map = nullptr;
}
MobHead::MobHead(int clrsCount, unsigned int mapSizeDegree, std::string mapFileFullPath, std::string meshFileFullPath, std::string clrsMaterialsDirectoryPath, std::map<unsigned char,std::string> materialsPattern, unsigned char emptyMaterialPattern){
	colorsCount = clrsCount;
	materialsPaths = new std::string[clrsCount];
	graphicObjects = new GraphicObject[clrsCount];
	meshObject = std::shared_ptr<Mesh>(new Mesh());
	meshPath = meshFileFullPath;
	for (auto it = materialsPattern.begin(); it != materialsPattern.end(); *it++) {
		materials.push_back(std::shared_ptr<PhongMaterial>(new PhongMaterial()));
		materialsPaths[std::distance(materialsPattern.begin(), it)] = clrsMaterialsDirectoryPath + (*it).second;
	}
	if (mapSizeDegree > 10) {
		mapSizeDegree = 10;
		std::cout << "\nМакимально поддерживаемый размер - " << mapSizeDegree << " (" << pow(2, mapSizeDegree) << ")!";
	}
	else if (mapSizeDegree < 1) {
		mapSizeDegree = 1;
		std::cout << "\nРазмер не может быть менее - " << mapSizeDegree << " (" << pow(2, mapSizeDegree ) << ")!";
	}
	mapSize = pow(2, mapSizeDegree);
	map = new unsigned char** [mapSize];
	for (int i = 0; i < mapSize; i++) {
		map[i] = new unsigned char* [mapSize];
		for (int j = 0; j < mapSize; j++)
			map[i][j] = new unsigned char [mapSize];
	}
	loadMap(mapFileFullPath);
	loadMesh();
	loadMaterials();
	generateHead(materialsPattern, emptyMaterialPattern);
}
MobHead::~MobHead() {
	for (auto i = headParts.begin(); i != headParts.end(); *i++) {
		i->second.clear();
	}
	headParts.clear();
	for (int i = 0; i < colorsCount; i++) {
		materialsPaths[i].clear();
		materials[i].reset();
	}
	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++)
			delete[] map[i][j];
		delete[] map[i];
	}
	delete[] map;
	delete[] graphicObjects;
	delete[] materialsPaths;
	meshPath.clear();
}
void MobHead::generateHead(std::map<unsigned char, std::string>& materialsPattern, unsigned char& emptyMaterialPattern) {
	modelMatrix = glm::mat4(1.0);
	for (int i = 0; i < mapSize; i++) {
		headParts.push_back(std::pair<bool, std::vector<GameObject>>());
		headParts[i].first = true;
		for (int j = 0; j < mapSize; j++) {
			for (int k = 0; k < mapSize; k++) {
				if (map[i][j][k] != emptyMaterialPattern)
				[&] {
					for (auto it = materialsPattern.begin(); it != materialsPattern.end(); *it++)
						if (it->first == map[i][j][k]) {
							GameObject tempObject;
							tempObject.setGraphicObject(graphicObjects[std::distance(materialsPattern.begin(), it)]);
							tempObject.setPosition(glm::vec3(i - mapSize / 2, j - mapSize / 2, k - mapSize / 2));
							headParts[i].second.push_back(tempObject);
							return;
						}
				}();

			}
		}
	}
	std::reverse(headParts.begin(), headParts.end());
}
void MobHead::loadMap(std::string fileNameFullPath) {
	std::ifstream mapFile(fileNameFullPath.c_str(), std::ios_base::in);
	if (mapFile.is_open()) {
		mapFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			int i = mapSize - 1;
			while (!mapFile.eof() && i >= 0) {
				for (int j = mapSize - 1; j >= 0; j--)
					for (int k = mapSize - 1; k >= 0; k--)
						mapFile >> map[i][j][k];
				i--;
			}
		}
		catch (std::exception e) {
			msg::error::outErrMessage(fileNameFullPath, msg::error::errType::FILE_BROKEN, e);
		}
	}
	else {
		msg::error::outErrMessage(fileNameFullPath, msg::error::errType::FILE_NOT_EXIST);
	}
}
void MobHead::loadMesh() {
	meshObject->load(meshPath);
	for (int i = 0; i < colorsCount; i++)
		graphicObjects[i].setMesh(meshObject);
}
void MobHead::loadMaterials() {
	for (int i = 0; i < colorsCount; i++) {
		materials[i]->load(materialsPaths[i]);
		graphicObjects[i].setLightMaterial(materials[i]);
	}
}
void MobHead::draw(void) {
	glPushMatrix();
	glMultMatrixf(glm::value_ptr(modelMatrix));
	for (auto i = headParts.begin(); i != headParts.end();  *i++)
		if (i->first == true)
			for (auto j = i->second.begin(); j != i->second.end(); *j++)
				j->draw();
	glPopMatrix();
}
void MobHead::keyboardFunction(unsigned char key, void(*disabledFn)(unsigned char k, int x, int y)) {
	if ((key >= '0' && key <= '9')) {
		int index = key - '0';
		if(index > mapSize - 1)
			return;
		headParts[index].first = headParts[index].first ?  false : true;
		std::cout << "Слой №" << index << ", видимость: " << std::boolalpha << headParts[index].first << std::noboolalpha << "\n$ " << typeid(MobHead).name() << " >>> ";
	}
	if (key == 'q' || key == 'Q') {
		std::cout << "\nВыход из функции управления слоями " << typeid(MobHead).name() << ".";
		glutKeyboardFunc(disabledFn);
	}
}
