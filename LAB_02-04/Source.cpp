#include <GL/freeglut.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <windows.h>
#include <iostream>
#include "GObject.h"
#include "CameraFree.h"
#include "CameraFixed.h"
#include <string>

const char* title = "LAB_2-3 Romanov R. I. IVT-41-19";
const int gObjectCount = 4;
int windowSizeX = 1024, windowSizeY = 768;

GLfloat objectsPositions[gObjectCount][3] = {
	{-4.0f,0,0}, {0,0,4.0f}, {0,0,-4.0f}, {4.0f,0,0}
};
GLfloat objectsAngles[gObjectCount] = {
	0.0f, 90.0f, -90.0f, -180.0f
};
GLfloat objectsColors[gObjectCount][3] = {
	{0.09f, 0.65f, 0.38f}, {0.99f, 0.26f, 0.39f}, {1.0f, 1.0f, 0}, {0.22f, 0, 1.0f}
};
GLfloat objectSize = 1.0f;

GObject** gObjects;
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
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (cameraState == 1) {
		camera1.apply();
	}
	else if (cameraState == 2){
		camera2.apply();
	}
	for (int i = 0; i < gObjectCount; i++)
		gObjects[i]->draw();
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
	}
}

int main(int argc, char** argv) {
	QueryPerformanceFrequency(&frequency);
	setlocale(0, "");
	system("Color 0a");
	std::cout.precision(5);
	gObjects = new GObject * [gObjectCount];
	for (int i = 0; i < gObjectCount; i++)
		gObjects[i] = new GObject(objectsPositions[i], objectsAngles[i], objectsColors[i], objectSize);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(windowSizeX, windowSizeY);
	glutCreateWindow(title);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Simulation);
	glutKeyboardFunc(Keyboard);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	QueryPerformanceCounter(&newTick);
	newSimTick = newTick;
	glutMainLoop();
	for (int i = 0; i < gObjectCount; i++) 
		delete[i] gObjects[i];
	delete[] gObjects;
	return 0;
}