#ifndef SIMULATION_H
#define SIMULATION_H
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "projectGlobalConst.h"
#include "Data.h"
#include <vector>
#include <algorithm>
#include <random>
extern inline double thisDelta(LARGE_INTEGER& nTick, LARGE_INTEGER& oTick);
extern inline double getSimTime();
extern inline void cameraSimulation(GLfloat simulationTime);
extern inline void gameObjectsSimulation(GLfloat simulationTime);
extern inline void movePlayer();
extern inline void moveMonster(std::shared_ptr<GameObject>& monsterObj);
extern void Simulation();

inline gameObjectConst::MoveDirectionState getDir(glm::ivec2 offset);
inline std::vector<gameObjectConst::MoveDirectionState> getPossibleDirs(std::vector<gameObjectConst::MoveDirectionState>& wrongDirs);
inline void movePlayerInstructions(int xOffset, int yOffset, int xOffset2nd, int yOffset2nd, gameObjectConst::MoveDirectionState dir);
inline glm::ivec2 getOffset(gameObjectConst::MoveDirectionState dir);
inline void outMap();
#endif // !SIMULATION_H

