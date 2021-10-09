#include <GL/freeglut.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <windows.h>
#include <iostream>
#include "GObject.h"
#include "Camera.h"
#include <string>

const char* title = "LAB_2 Romanov R. I. IVT-41-19";
const int gObjectCount = 4;

GLfloat objectsPositions[gObjectCount][3] = {
	{-4.0f,0,0}, {0,0,4.0f}, {0,0,-4.0f}, {4.0f,0,0}
};
GLfloat objectsAngles[gObjectCount] = {
	0.0f, 90.0f, -90.0f, -180.0f
};
GLfloat objectsColors[gObjectCount][3] = {
	{1.0f, 1.0f, 1.0f}, {1.0f, 0, 0}, {0, 1.0f, 0}, {0, 0, 1.0f}
};
GLfloat objectSize = 1.0f;

GObject** gObjects;
Camera camera;

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
		std::string tmp2 = tmp1 + " | FPS: " + std::to_string((double)framesValue / delta);
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
	camera.setKey(CameraLeft, CameraRight,
		CameraUp, CameraDown,
		CameraForward, CameraBackward);
	camera.simulate(simTimePassed);
	glutPostRedisplay();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (double)w / h, 0.2, 70.0);
}

void Display(void) {
	QueryPerformanceCounter(&newTick);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.apply();
	for (int i = 0; i < gObjectCount; i++)
		gObjects[i]->draw();
	glutSwapBuffers();
	outFPS();
	framesValue++;
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
	glutInitWindowSize(1024, 768);
	glutCreateWindow(title);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Simulation);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	QueryPerformanceCounter(&newTick);
	newSimTick = newTick;
	glutMainLoop();
	for (int i = 0; i < gObjectCount; i++) 
		delete[i] gObjects[i];
	delete[] gObjects;
	return 0;
}