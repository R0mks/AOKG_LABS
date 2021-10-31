#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GLM/glm.hpp>

#include <windows.h>
#include <iostream>
#include "GObject.h"
#include "Camera.h"
#include "Light.h"
#include <string>
#include <vector>
#include <limits>

const char* title = "LAB_5 Romanov R. I. IVT-41-19";
const int gObjectCount = 4;
int windowSizeX = 1024, windowSizeY = 768;
int windowPosX = 300, windowPosY = 300;
std::string currentWorkingDirectory;

glm::vec4 globalClearColor = glm::vec4(0.0,0.0,0.0,1.0f);
glm::vec3 objectsPositions[gObjectCount] = {
	glm::vec3(-4.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, -4.0f), glm::vec3(4.0f, 0.0f, 0.0f)
};
GLfloat objectsAngles[gObjectCount] = {
	0.0f, 90.0f, -90.0f, -180.0f
};
glm::vec3 objectsColors[gObjectCount] = {
	glm::vec3(0.09f, 0.65f, 0.38f), glm::vec3(0.99f, 0.26f, 0.39f), glm::vec3(1.0f, 1.0f, 0), glm::vec3(0.22f, 0, 1.0f)
};
GLfloat objectSize = 1.0f;

std::vector<std::shared_ptr<GObject>> gObjects;
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
std::string GObjectMaterialPath[gObjectCount] = {
	"\\phongmaterialsdata\\gobject-1.phmat",
	"\\phongmaterialsdata\\gobject-2.phmat",
	"\\phongmaterialsdata\\gobject-3.phmat",
	"\\phongmaterialsdata\\gobject-4.phmat"
};
std::string lightSettingsPath = "\\phongmaterialsdata\\light-1.lgt";

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
	for (int i = 0; i < gObjectCount; i++)
		gObjects[i]->draw();
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
	} break;
	case 'm': case 'M': {
		for (int i = 0; i < gObjectCount; i++) {
			materials[i]->load(currentWorkingDirectory + GObjectMaterialPath[i]);
			gObjects[i]->setLightMaterial(materials[i]);
		}
		std::cout << "\nМатериалы обновлены!";
	}; break;
	case 'l': case 'L': {
		light.load(currentWorkingDirectory + lightSettingsPath);
		std::cout << "\nСвет обновлён!";
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
	for (int i = 0; i < gObjectCount; i++) {
		gObjects.push_back(std::shared_ptr<GObject>(new GObject(objectsPositions[i], objectsAngles[i], objectsColors[i], objectSize)));
		materials.push_back(std::shared_ptr<PhongMaterial>(new PhongMaterial()));
		materials[i]->load(currentWorkingDirectory + GObjectMaterialPath[i]);
		gObjects[i]->setLightMaterial(materials[i]);
	}
	QueryPerformanceFrequency(&frequency);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
	glutInitWindowPosition(windowPosX, windowPosY);
	glutInitWindowSize(windowSizeX, windowSizeY);
	glutCreateWindow(title);
	glewInit();
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientColor);
	std::cout << "GL_VENDOR: " << glGetString(GL_VENDOR);
	std::cout << "\nGL_RENDERER: " << glGetString(GL_RENDERER);
	std::cout << "\nGL_VERSION: " << glGetString(GL_VERSION);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Simulation);
	glutKeyboardFunc(Keyboard);
	//glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	QueryPerformanceCounter(&newTick);
	newSimTick = newTick;
	glutMainLoop();
	return 0;
}