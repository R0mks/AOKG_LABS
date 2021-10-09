#include <stdio.h>
#include <windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/freeglut.h>
#include <iostream>

const int simulationTimerCount = 20;
double const defaultRotateX = 5.0, defaultRotateY = 5.0, defaultRotateZ = 7.5;
double rotateX = defaultRotateX, rotateY = defaultRotateY, rotateZ = defaultRotateZ;

const int colorsCount = 4;
struct colors {
	double r;
	double g;
	double b;
};
colors teapotColor, teacupColor;
colors defaultTeapotColor;
colors colorsArray[colorsCount];


bool teapotColorReplaceSwitch = false;
int teapotColorIterator = 0;
const double teapotColorReplaceTimer_limit = 1000;
double teapotColorReplaceTimer_countdown = 0;

void setColors() {
	defaultTeapotColor.r = 1.0;
	defaultTeapotColor.g = 0;
	defaultTeapotColor.b = 0;
	teacupColor.r = 0;
	teacupColor.g = 0;
	teacupColor.b = 1.0;
	colorsArray[0].r = 0.0; colorsArray[0].g = 0.0; colorsArray[0].b = 0.0;
	colorsArray[1].r = 1.0; colorsArray[1].g = 1.0; colorsArray[1].b = 1.0;
	colorsArray[2].r = 1.0; colorsArray[2].g = 0.0; colorsArray[2].b = 0.0;
	colorsArray[3].r = 0.0; colorsArray[3].g = 0.0; colorsArray[3].b = 1.0;
}
void changeTeapotColor(colors color) {
	std::cout << "Color " << teapotColorIterator << " : "
		<< color.r << ","
		<< color.g << ","
		<< color.b << "\n";
	teapotColor.r = color.r;
	teapotColor.g = color.g;
	teapotColor.b = color.b;
}
//-----
void Simulation(int value) {
	glutPostRedisplay();
	if (teapotColorReplaceSwitch) {
		if (teapotColorReplaceTimer_countdown >= teapotColorReplaceTimer_limit) {
			if (teapotColorIterator > colorsCount - 1)
				teapotColorIterator = 0;
			teapotColor.r = colorsArray[teapotColorIterator].r;
			teapotColor.g = colorsArray[teapotColorIterator].g;
			teapotColor.b = colorsArray[teapotColorIterator].b;
			std::cout << "\n" << teapotColor.r << "," << teapotColor.g << "," << teapotColor.b;
			teapotColorIterator++;
			teapotColorReplaceTimer_countdown = 0;
		}
		teapotColorReplaceTimer_countdown += double(teapotColorReplaceTimer_limit / simulationTimerCount);
	}
	glutTimerFunc(simulationTimerCount,Simulation,0);
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (double)w / h, 0.2, 70.0);

}

void Display() {
	glClearColor(0.0f, 0.9f, 0.25f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(rotateX, rotateY, rotateZ, 0, 0, 0, 0, 1, 0);
	glColor3f(teapotColor.r, teapotColor.g, teapotColor.b);
	glutWireTeapot(1.0);
	glColor3f(0.0, 0.0, 1.0);
	glutWireTeacup(1.0);
	glutSwapBuffers();
}

void KeyboardFunc(unsigned char key,int x, int y) {
	printf("Код клавиши - %i \n", key );
	switch (key) {
	case 'a': case 'A': {
		rotateX += 0.1;
	};  break;
	case 'd': case 'D': {
		rotateX -= 0.1;
	};  break;
	case 'w': case 'W': {
		rotateY += 0.1;
	};  break;

	case 's': case 'S': {
		rotateY -= 0.1;
	};  break;
	case 'r': case 'R': {
		rotateX = defaultRotateX;
		rotateY = defaultRotateY;
		rotateZ = defaultRotateZ;
		teapotColor.r = defaultTeapotColor.r;
		teapotColor.g = defaultTeapotColor.g;
		teapotColor.b = defaultTeapotColor.b;
		teapotColorReplaceSwitch = false;
		teapotColorReplaceTimer_countdown = 0;
		teapotColorIterator = 0;
		system("cls");
	}; break;
	case '+': {
		changeTeapotColor(colorsArray[teapotColorIterator]);
		teapotColorIterator++;
		teapotColorIterator > colorsCount - 1 ?
			teapotColorIterator = 0 : 0;
	}; break;
	case '-': {
		changeTeapotColor(colorsArray[teapotColorIterator]);
		teapotColorIterator--;
		teapotColorIterator < 0 ?
			teapotColorIterator = colorsCount - 1 : 0;
	}; break;
	case 'e': case 'E': {
		teapotColorReplaceSwitch ?
			(teapotColorReplaceSwitch = false, teapotColorReplaceTimer_countdown = 0) :
			teapotColorReplaceSwitch = true;
	}; break;
	}
}

int main(int argc, char ** argv) {
	setlocale(0, "");
	system("cls");
	system("Color 0a");
	std::cout.precision(2);
	setColors();
	teapotColor.r = defaultTeapotColor.r;
	teapotColor.g = defaultTeapotColor.g;
	teapotColor.b = defaultTeapotColor.b;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(1024,768);
	glutCreateWindow("LAB_1 Romanov R. I. IVT-41-19");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutTimerFunc(20, Simulation, 0);
	glutKeyboardFunc(KeyboardFunc);
	glutMainLoop();
	return 0;
} 