#ifndef DATA_H
#define DATA_H
#include <GL/glew.h>
#include <GLM/glm.hpp>

#include <string>

#include "Light.h"
#include "Camera.h"
#include "GameObject.h"
#include "GraphicObject.h"
#include "GameObjectFactory.h"

extern const char* title;
extern const int graphicObjectCount;
extern int windowSizeX, windowSizeY;
extern int windowPosX, windowPosY;
extern std::string currentWorkingDirectory;

extern unsigned char cameraState;
extern LARGE_INTEGER newTick, oldTick, frequency;
extern LARGE_INTEGER newSimTick, oldSimTick;
extern int framesValue;

extern glm::vec4 globalClearColor;
extern glm::vec3 objectSize;

constexpr int mapSize = 21;

extern GameObjectFactory gameObjectFactory;
extern std::shared_ptr<GameObject> player;
extern GraphicObject planeGraphicObject;
extern std::shared_ptr<GameObject> gameObjects[mapSize][mapSize];
extern int passabilityMap[mapSize][mapSize];

/// <summary>
/// FIXED CAMERA
/// </summary>
extern CameraFixed camera1;
/// <summary>
/// FREE CAMERA (NOCLIP)
/// </summary>
extern CameraFree camera2;
extern Light light;

extern std::string jsonPropeties;
extern std::string lightSettingsPath;
extern GLfloat globalAmbientColor[];

extern void initData(std::string directoryPath, std::string propetiesPath);
extern void clearData();
#endif DATA_H
