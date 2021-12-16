#ifndef SIMULATION_H
#define SIMULATION_H
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "projectGlobalConst.h"
#include "Data.h"
extern inline double thisDelta(LARGE_INTEGER& nTick, LARGE_INTEGER& oTick);
extern inline double getSimTime();
extern inline void cameraSimulation(GLfloat simulationTime);
extern inline void gameObjectsSimulation(GLfloat simulationTime);
extern inline void movePlayer();
extern void Simulation();

inline void movePlayerInstructions(int xOffset, int yOffset, int xOffsetBehind, int yOffsetBehind, gameObjectConst::MoveDirectionState dir);
inline void outMap();
#endif // !SIMULATION_H

