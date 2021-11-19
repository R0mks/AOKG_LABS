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
#include "additionalFunctions.hpp"
#include "MobHead.h";

const char* title = "LAB_6 Romanov R. I. IVT-41-19";
const int graphicObjectCount = 3;
int windowSizeX = 1024, windowSizeY = 768;
int windowPosX = 300, windowPosY = 300;
void(*disabledKeyboardFunction)(unsigned char k, int x, int y);
std::string currentWorkingDirectory;

glm::vec4 globalClearColor = glm::vec4(0.0,0.0,0.0,1.0f);
glm::vec3 objectSize = glm::vec3(1.0f, 1.0f, 1.0f);

/// <summary>
/// FIXED CAMERA
/// </summary>
CameraFixed camera1;
/// <summary>
/// FREE CAMERA (NOCLIP)
/// </summary>
CameraFree camera2;
unsigned char cameraState = 1;
LARGE_INTEGER newTick, oldTick, frequency;
LARGE_INTEGER newSimTick, oldSimTick;
int framesValue;


GLfloat globalAmbientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
Light light;
std::vector<std::shared_ptr<PhongMaterial>> materials;
std::string graphicObjectMaterialPath[graphicObjectCount] = {
	"\\data\\materials\\Box.phmat",
	"\\data\\materials\\ChamferBox.phmat",
	"\\data\\materials\\Box2.phmat"
};
std::string lightSettingsPath = "\\data\\materials\\light-1.lt";

std::map<int, GraphicObject> graphicObjects;
std::vector<std::shared_ptr<Mesh>> meshes;
std::string meshesPath[graphicObjectCount] = {
	"\\data\\meshes\\Box.obj",
	"\\data\\meshes\\ChamferBox.obj",
	"\\data\\meshes\\Box.obj"
};

std::shared_ptr<PhongMaterial> planeMaterial;
std::shared_ptr<Mesh> planeMesh;
GraphicObject planeGraphicObject;
GameObject planeGameObject;
std::string planeMaterialPath = "\\data\\materials\\SimplePlane.phmat";
std::string planeMeshPath = "\\data\\meshes\\SimplePlane.obj";
const int passabilityMapSize = 21;
std::shared_ptr<GameObject> mapObjects[passabilityMapSize][passabilityMapSize];
int passabilityMap[passabilityMapSize][passabilityMapSize] = {
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
MobHead creeperHead;//защита
void creeperHeadInit() {//защита
	const int materialsCount = 8;
	std::map<unsigned char, std::string> materialsPattern;
	unsigned char emptyMatterialPattern = static_cast<unsigned char>(48);
	std::string materialFileNames[materialsCount]{
		"box1.phmat","box2.phmat","box3.phmat","box4.phmat","box5.phmat","box6.phmat","box7.phmat","box8.phmat"
	};
	for (int i = 0; i < materialsCount; i++) {
		materialsPattern.insert(std::pair<unsigned char, std::string>(static_cast<unsigned char>(49 + i), materialFileNames[i]));
	}
	creeperHead = MobHead(materialsCount, 3, currentWorkingDirectory + "\\data\\maps\\CreeperObj.map", currentWorkingDirectory + "\\data\\meshes\\box.obj", currentWorkingDirectory +  "\\data\\materials\\CreeperHead\\", materialsPattern, emptyMatterialPattern);
}


void (*drawInstructions)();
const int drawInstructionsCount = 2;
int drawInstructionsNumber;
inline void drawInstructions1() {
	planeGameObject.draw();
	for (int i = 0; i < passabilityMapSize; i++)
		for (int j = 0; j < passabilityMapSize; j++)
			if (mapObjects[i][j] != nullptr)
				mapObjects[i][j]->draw();
}
inline void drawInstructions2() {
	creeperHead.draw();
}
void (*drawInstructionsCollection[drawInstructionsCount])() = {
	drawInstructions1, drawInstructions2
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
	bool CameraLeft = GetAsyncKeyState(VK_LEFT);
	bool CameraRight = GetAsyncKeyState(VK_RIGHT);
	bool CameraUp = GetAsyncKeyState(VK_UP);
	bool CameraDown = GetAsyncKeyState(VK_DOWN);
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

void KeyboardCreeperHead(unsigned char key, int x, int y) {
	creeperHead.keyboardFunction(key, disabledKeyboardFunction);
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
		for (int i = 0; i < graphicObjectCount; i++) {
			materials[i]->load(currentWorkingDirectory + graphicObjectMaterialPath[i]);
			graphicObjects[i].setLightMaterial(materials[i]);
			planeMaterial->load(currentWorkingDirectory + planeMaterialPath);
			planeGraphicObject.setLightMaterial(planeMaterial);
		}
		std::cout << "\nМатериалы обновлены!";
	}; break;
	case 'l': case 'L': {
		light.load(currentWorkingDirectory + lightSettingsPath);
		std::cout << "\nСвет обновлён!";
	}; break;
	case 'c': case 'C': {
		std::cout << "\nПереход в функцию управления слоями " << typeid(MobHead).name() << "\n$ " << typeid(MobHead).name() << " >>> ";
		changeKeyboardFunction(Keyboard, KeyboardCreeperHead);
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
	planeMaterial = std::shared_ptr<PhongMaterial>(new PhongMaterial());
	planeMesh = std::shared_ptr<Mesh>(new Mesh());
	planeMaterial->load(currentWorkingDirectory + planeMaterialPath);
	planeMesh->load(currentWorkingDirectory + planeMeshPath);
	planeGraphicObject.setLightMaterial(planeMaterial);
	planeGraphicObject.setMesh(planeMesh);
	planeGraphicObject.setPosition(glm::vec3(0.0f, -0.5f, 0.0f));
	planeGameObject.setGraphicObject(planeGraphicObject);
	for (int i = 0; i < graphicObjectCount; i++) {
		graphicObjects.insert(std::pair<int,GraphicObject>(i, GraphicObject()));
		meshes.push_back(std::shared_ptr<Mesh>(new Mesh()));
		meshes[i]->load(currentWorkingDirectory + meshesPath[i]);
		materials.push_back(std::shared_ptr<PhongMaterial>(new PhongMaterial()));
		materials[i]->load(currentWorkingDirectory + graphicObjectMaterialPath[i]);
		graphicObjects[i].setLightMaterial(materials[i]);
		graphicObjects[i].setMesh(meshes[i]);
	}
	addFns::fillMapObjects(passabilityMap,mapObjects,passabilityMapSize,graphicObjects);
	creeperHeadInit();
	drawInstructions = drawInstructions1;
	drawInstructionsNumber = 0;
	QueryPerformanceFrequency(&frequency);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
	glutInitWindowPosition(windowPosX, windowPosY);
	glutInitWindowSize(windowSizeX, windowSizeY);
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
	planeMaterial.reset();
	planeMesh.reset();
	for (int i = 0; i < passabilityMapSize; i++)
		for (int j = 0; j < passabilityMapSize; j++)
			mapObjects[i][j].reset();
	for (auto e : materials)
		e.reset();
	for (auto e : meshes)
		e.reset();
	graphicObjects.clear();
	return 0;
}