#include <GL/glew.h>

#include <GL/freeglut.h>
#include <GL/GLU.h>
#include <GLM/glm.hpp>

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <map>

#include "globalFunctions.h"
#include "GraphicObject.h"
#include "Camera.h"
#include "Light.h"
#include "Mesh.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "additionalFunctions.hpp"

const char* title = "LAB_7 Romanov R. I. IVT-41-19";
const int graphicObjectCount = 3;
int windowSizeX = 1024, windowSizeY = 768;
int windowPosX = 300, windowPosY = 300;
void(*disabledKeyboardFunction)(unsigned char k, int x, int y);
std::string currentWorkingDirectory;

glm::vec4 globalClearColor = glm::vec4(0.0,0.0,0.0,1.0f);
glm::vec3 objectSize = glm::vec3(1.0f, 1.0f, 1.0f);

unsigned char cameraState = 1;
LARGE_INTEGER newTick, oldTick, frequency;
LARGE_INTEGER newSimTick, oldSimTick;
int framesValue;

std::string jsonPropeties = "\\data\\GameObjectsGraphicPropeties.json";
std::string lightSettingsPath = "\\data\\materials\\light-1.lt";
GLfloat globalAmbientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };

const int mapSize = 21;

GameObjectFactory gameObjectFactory;
std::shared_ptr<GameObject> player;
GraphicObject planeGraphicObject;
std::shared_ptr<GameObject> mapObjects[mapSize][mapSize];
extern int passabilityMap[mapSize][mapSize] = {
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
/// <summary>
/// FIXED CAMERA
/// </summary>
CameraFixed camera1;
/// <summary>
/// FREE CAMERA (NOCLIP)
/// </summary>
CameraFree camera2;
Light light;
void initData(std::string directoryPath, std::string propetiesPath) {
	light.load(currentWorkingDirectory + lightSettingsPath);
	gameObjectFactory.loadData(directoryPath, propetiesPath);
	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++) {
			double x = static_cast<double>(i) - mapSize / 2, y = static_cast<double>(j) - mapSize / 2;
			switch (passabilityMap[i][j]) {
			case 1: mapObjects[i][j] = gameObjectFactory.create(GameObjectType::LIGHT_OBJECT, x, y); break;
			case 2: mapObjects[i][j] = gameObjectFactory.create(GameObjectType::HEAVY_OBJECT, x, y); break;
			case 3: mapObjects[i][j] = gameObjectFactory.create(GameObjectType::BORDER_OBJECT, x, y); break;
			default: mapObjects[i][j] = nullptr; break;
			}
		}
	}
	player = gameObjectFactory.create(GameObjectType::PLAYER, 19 - mapSize/2, 1 - mapSize/2);
	planeGraphicObject.setPosition(glm::vec3(0, -0.5, 0));
	std::shared_ptr<Mesh> planeMesh = std::make_shared<Mesh>();
	planeMesh->load(directoryPath+"\\data\\meshes\\HighPolyPlane.obj");
	planeGraphicObject.setMesh(planeMesh);
	std::shared_ptr<PhongMaterial> planeMaterial = std::make_shared<PhongMaterial>();
	planeMaterial->load(directoryPath+"\\data\\materials\\PlaneMaterial.phmat");
	planeGraphicObject.setLightMaterial(planeMaterial);
};

void (*drawInstructions)();
const int drawInstructionsCount = 1;
int drawInstructionsNumber;
inline void drawInstructions1() {
	planeGraphicObject.draw();
	for (int i = 0; i < mapSize; i++)
		for (int j = 0; j < mapSize; j++)
			if (mapObjects[i][j] != nullptr)
				mapObjects[i][j]->draw();
	player->draw();
}
void (*drawInstructionsCollection[drawInstructionsCount])() = {
	drawInstructions1
};

inline double thisDelta(LARGE_INTEGER &nTick, LARGE_INTEGER &oTick) {
	return double(nTick.QuadPart - oTick.QuadPart) / frequency.QuadPart;
}

inline double getSimTime() {
	oldSimTick = newSimTick;
	QueryPerformanceCounter(&newSimTick);
	return thisDelta(newSimTick, oldSimTick);
}

void outFPS() {
	QueryPerformanceCounter(&newTick);
	double delta = thisDelta(newTick, oldTick);
	if (delta > 0.5) {
		std::string tmp1(title);
		std::string tmp2 = tmp1 + " | FPS: " + std::to_string((int)(framesValue / delta));
		const char* tmpChar = tmp2.c_str();
		glutSetWindowTitle(tmpChar);
		framesValue = 0;
		oldTick = newTick;
	}
}

void Simulation() {
	double simTimePassed = getSimTime();
	bool CameraLeft = GetAsyncKeyState(0x41); // KEY A
	bool CameraRight = GetAsyncKeyState(0x44); // KEY D
	bool CameraUp = GetAsyncKeyState(0x57); // KEY W
	bool CameraDown = GetAsyncKeyState(0x53); // KEY S
	bool CameraForward = GetAsyncKeyState(VK_ADD);
	bool CameraBackward = GetAsyncKeyState(VK_SUBTRACT);
	if (cameraState == 1) {
		camera1.setKey(CameraLeft, CameraRight,
			CameraUp, CameraDown,
			CameraForward, CameraBackward);
		camera1.simulate(simTimePassed);
	}
	else if (cameraState == 2) {
		camera2.setKey(CameraUp, CameraDown, CameraLeft, CameraRight);
		camera2.simulate(simTimePassed);
	}
	glutPostRedisplay();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (double)w / h, 0.1, 100.0);
}

void Display(void) {
	QueryPerformanceCounter(&newTick);
	glClearColor(globalClearColor.x,globalClearColor.y,globalClearColor.z,globalClearColor.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_LIGHTING);
	if (cameraState == 1) {
		camera1.apply();
	}
	else if (cameraState == 2){
		camera2.apply();
	}
	light.apply(GL_LIGHT0);
	drawInstructions();
	glDisable(GL_LIGHTING);
	glutSwapBuffers();
	outFPS();
	framesValue++;
}

inline void mouseCallback(int x, int y) {
	camera2.mouseCallback(x, y);
}
inline void mouseCallbackSaveLastXY(int button, int state, int x, int y) {
	camera2.mouseCallbackSaveLastXY(button, state, x, y);
}

void changeKeyboardFunction(void (*oldFunction)(unsigned char key, int x, int y), void (*newFunction)(unsigned char key, int x, int y)) {
	disabledKeyboardFunction = oldFunction;
	glutKeyboardFunc(newFunction);
}

void Keyboard(unsigned char key, int x, int y){
	switch (key) {
	case '1': {
		std::cout << "\nВыбрана камера 1: Фиксированная камера!";
		cameraState = 1;
		glutMouseFunc(NULL);
		glutMotionFunc(NULL);
	}; break;
	case '2': {
		std::cout << "\nВыбрана камера 2: Свободная камера!";
		cameraState = 2;
		camera2.getLastXYForCamera();
		glutMouseFunc(mouseCallbackSaveLastXY);
		glutMotionFunc(mouseCallback);
	}; break;
	case 'r': case 'R': {
		std::cout << "\nКамера 2 сброшена!";
		camera2.gotoCenter();
	}; break;
	case 'm': case 'M': {
		gameObjectFactory.loadData(currentWorkingDirectory,jsonPropeties);
		std::cout << "\nМатериалы обновлены!";
	}; break;
	case 'l': case 'L': {
		light.load(currentWorkingDirectory + lightSettingsPath);
		std::cout << "\nСвет обновлён!";
	}; break;
	case 'q': case'Q': {
		drawInstructionsNumber = 
			drawInstructionsNumber >= drawInstructionsCount - 1 ?
			0 : drawInstructionsNumber + 1;
		drawInstructions = drawInstructionsCollection[drawInstructionsNumber];
		std::cout << "\nИзменены отрисовочные инструкции, на  № " << drawInstructionsNumber + 1;
	}; break;
	}
}

int main(int argc, char** argv) {
	setlocale(0, "");
	system("Color 0a");
	std::cout.precision(5);
	currentWorkingDirectory = std::string(argv[0]);
	int pos = currentWorkingDirectory.find_last_of("/\\");
	currentWorkingDirectory = currentWorkingDirectory.substr(0, pos);
	drawInstructions = drawInstructions1;
	drawInstructionsNumber = 0;
	QueryPerformanceFrequency(&frequency);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
	glutInitWindowPosition(windowPosX, windowPosY);
	glutInitWindowSize(windowSizeX, windowSizeY);
	initData(currentWorkingDirectory,jsonPropeties);
	glutCreateWindow(title);
	glewExperimental = GL_TRUE;
	glewInit();
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientColor);
	std::cout << "GL_VENDOR: " << glGetString(GL_VENDOR);
	std::cout << "\nGL_RENDERER: " << glGetString(GL_RENDERER);
	std::cout << "\nGL_VERSION: " << glGetString(GL_VERSION);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Simulation);
	glutKeyboardFunc(Keyboard);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	QueryPerformanceCounter(&newTick);
	newSimTick = newTick;
	glutMainLoop();
	for (int i = 0; i < mapSize; i++)
		for (int j = 0; j < mapSize; j++)
			mapObjects[i][j].reset();
	return 0;
}