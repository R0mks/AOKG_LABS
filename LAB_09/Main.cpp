#include <GL/glew.h>

#include <GL/freeglut.h>
#include <GL/GLU.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <GLM/glm.hpp>

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <map>

#include "globalFunctions.h"
#include "Data.h"
#include "Simulation.h"

#include "GraphicObject.h"
#include "Camera.h"
#include "Light.h"
#include "Mesh.h"
#include "GameObject.h"
#include "GameObjectFactory.h"


void(*disabledKeyboardFunction)(unsigned char k, int x, int y);

void (*drawInstructions)();
const int drawInstructionsCount = 1;
int drawInstructionsNumber;
inline void drawInstructions1() {
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	planeGraphicObject.draw();
	Texture::disableAll();
	for (int i = 0; i < mapSize; i++)
		for(int j = 0; j < mapSize; j++)
			if(gameObjects[i][j] != nullptr)
				gameObjects[i][j]->draw();
	if (player != nullptr) {
		player->draw();
	}
	for (int i = 0; i < monsterCount; i++)
		if(monster[i] != nullptr)
			monster[i]->draw();
}
void (*drawInstructionsCollection[drawInstructionsCount])() = {
	drawInstructions1
};

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

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (double)w / h, 0.1, 100.0);
}

void Display(void) {
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
	glutCreateWindow(title);
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cout << "Error: " << glewGetErrorString(err) << "\n";
	}
	std::cout << "Using GLEW " << glewGetString(GLEW_VERSION);
	std::cout << "\nGL_VENDOR: " << glGetString(GL_VENDOR);
	std::cout << "\nGL_RENDERER: " << glGetString(GL_RENDERER);
	std::cout << "\nGL_VERSION: " << glGetString(GL_VERSION);
	ilInit();
	iluInit();
	ilutInit();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Simulation);
	glutKeyboardFunc(Keyboard);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	QueryPerformanceCounter(&newTick);
	newSimTick = newTick;
	initData(currentWorkingDirectory, jsonPropeties);
	glutMainLoop();
	clearData();
	return 0;
}