#include "Data.h"
const char* title = "LAB_9 Romanov R. I. IVT-41-19";
const int graphicObjectCount = 3;
int windowSizeX = 1024, windowSizeY = 768;
int windowPosX = 300, windowPosY = 300;
std::string currentWorkingDirectory;

unsigned char cameraState = 1;
LARGE_INTEGER newTick, oldTick, frequency;
LARGE_INTEGER newSimTick, oldSimTick;
int framesValue;

glm::vec4 globalClearColor = glm::vec4(0.0, 0.0, 0.0, 1.0f);
glm::vec3 objectSize = glm::vec3(1.0f, 1.0f, 1.0f);

GameObjectFactory gameObjectFactory;
std::shared_ptr<GameObject> player;
std::shared_ptr<GameObject> monster[monsterCount];
GraphicObject planeGraphicObject;
std::shared_ptr<GameObject> gameObjects[mapSize][mapSize];

int playerPosX = 19, playerPosY = 1;
std::pair<int, int> monsterPosXY[monsterCount] = {
	std::pair<int,int>(1,1), std::pair<int,int>(1,19), std::pair<int,int>(19,19)
};

CameraFixed camera1;
CameraFree camera2;
Light light;

std::string jsonPropeties = "\\data\\GameObjectsGraphicPropeties.json";
std::string lightSettingsPath = "\\data\\materials\\light-1.lt";
GLfloat globalAmbientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };

int passabilityMap[mapSize][mapSize] = {
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,0,3,
	3,0,2,1,2,0,2,0,2,2,2,1,2,0,2,0,2,0,2,2,3,
	3,0,2,0,2,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,3,
	3,0,1,0,2,2,1,2,2,0,2,0,2,2,2,1,2,0,2,0,3,
	3,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,2,0,3,
	3,0,2,2,1,1,2,0,2,0,2,2,2,2,2,0,2,2,2,0,3,
	3,0,2,0,0,0,2,0,2,0,0,0,0,0,2,0,0,0,0,0,3,
	3,0,2,0,2,2,2,0,2,0,2,2,1,2,2,2,1,2,2,0,3,
	3,0,0,0,2,0,0,0,2,0,2,0,0,0,0,0,0,0,1,0,3,
	3,2,2,2,2,0,2,2,2,0,2,0,2,2,2,2,2,2,2,0,3,
	3,0,0,0,2,0,0,0,1,0,2,0,0,0,2,0,0,0,0,0,3,
	3,0,2,0,2,2,2,0,2,1,2,0,2,2,2,0,2,2,2,2,3,
	3,0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,2,0,0,0,3,
	3,2,2,2,2,0,2,2,2,0,2,2,2,0,1,0,2,2,2,0,3,
	3,0,0,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,2,0,3,
	3,0,2,0,2,1,2,0,2,0,2,2,2,0,2,2,2,0,2,0,3,
	3,0,1,0,1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,3,
	3,0,2,1,2,0,2,2,2,2,2,0,2,0,2,0,2,2,2,2,3,
	3,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
};

void initData(std::string directoryPath, std::string propetiesPath) {
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientColor);
	PROJECT_SETTINGS::TEXTURE::init(PROJECT_SETTINGS::TEXTURE::FILTER::TRILINEAR);
	light.load(currentWorkingDirectory + lightSettingsPath);
	gameObjectFactory.loadData(directoryPath, propetiesPath);
	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++) {
			switch (passabilityMap[i][j]) {
			case 1: gameObjects[i][j] = gameObjectFactory.create(gameObjectConst::GameObjectType::LIGHT_OBJECT, mapSize, i, 0.5, j); break;
			case 2: gameObjects[i][j] = gameObjectFactory.create(gameObjectConst::GameObjectType::HEAVY_OBJECT, mapSize, i, 0.5, j); break;
			case 3: gameObjects[i][j] = gameObjectFactory.create(gameObjectConst::GameObjectType::BORDER_OBJECT, mapSize, i, 0.5, j); break;
			default: gameObjects[i][j] = nullptr; break;
			}
		}
	}
	for (int i = 0; i < monsterCount; i++)
		monster[i] = gameObjectFactory.create(gameObjectConst::GameObjectType::MONSTER, mapSize, monsterPosXY[i].first, 0.5, monsterPosXY[i].second);
	player = gameObjectFactory.create(gameObjectConst::GameObjectType::PLAYER, mapSize, playerPosX, 0.5, playerPosY);
	std::shared_ptr<Texture> planeTexture = std::make_shared<Texture>();
	planeTexture->load(directoryPath + "\\data\\textures\\plane\\sand.png");
	planeGraphicObject.setTexture(planeTexture);
	std::shared_ptr<Mesh> planeMesh = std::make_shared<Mesh>();
	planeMesh->load(directoryPath + "\\data\\meshes\\HighPolyPlane.obj");
	planeGraphicObject.setMesh(planeMesh);
	std::shared_ptr<PhongMaterial> planeMaterial = std::make_shared<PhongMaterial>();
	planeMaterial->load(directoryPath + "\\data\\materials\\PlaneMaterial.phmat");
	planeGraphicObject.setLightMaterial(planeMaterial);
	planeGraphicObject.setPosition(glm::vec3(0.0, 0.0, 0.0));
	planeMesh.reset();
	planeMaterial.reset();
	planeTexture.reset();
}
void clearData() {
	for (int i = 0; i < mapSize; i++)
		for (int j = 0; j < mapSize; j++)
			gameObjects[i][j].reset();
	player.reset();
}