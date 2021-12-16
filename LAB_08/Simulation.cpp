#include "Simulation.h"
inline double thisDelta(LARGE_INTEGER& nTick, LARGE_INTEGER& oTick) {
	return (double)(nTick.QuadPart - oTick.QuadPart) / frequency.QuadPart;
}
inline double getSimTime() {
	oldSimTick = newSimTick;
	QueryPerformanceCounter(&newSimTick);
	return thisDelta(newSimTick, oldSimTick);
}
inline void cameraSimulation(GLfloat simulationTime) {
	bool CameraLeft = GetAsyncKeyState(0x25); // KEY VK_LEFT
	bool CameraRight = GetAsyncKeyState(0x27); // KEY VK_RIGHT
	bool CameraUp = GetAsyncKeyState(0x26); // KEY VK_UP
	bool CameraDown = GetAsyncKeyState(0x28); // KEY VK_DOWN
	bool CameraForward = GetAsyncKeyState(VK_ADD);
	bool CameraBackward = GetAsyncKeyState(VK_SUBTRACT);
	if (cameraState == 1) {
		camera1.setKey(CameraLeft, CameraRight,
			CameraUp, CameraDown,
			CameraForward, CameraBackward);
		camera1.simulate(simulationTime);
	}
	else if (cameraState == 2) {
		camera2.setKey(CameraUp, CameraDown, CameraLeft, CameraRight);
		camera2.simulate(simulationTime);
	}
}
inline void gameObjectsSimulation(GLfloat simulationTime) {
	player->simulate(simulationTime);
	for (int i = 0; i < mapSize; i++)
		for (int j = 0; j < mapSize; j++)
			if (gameObjects[i][j] != nullptr)
				gameObjects[i][j]->simulate(simulationTime);
	//std::cout << std::endl << player->getGraphicPosition().x << ", " << player->getGraphicPosition().y << ", " << player->getGraphicPosition().z << ";";// ÎÒËÀÄÊÀ ÏÅÐÅÄÂÈÆÅÍÈß
}
inline void movePlayer() {
	bool moveUp = GetAsyncKeyState(0x57); // KEY W
	bool moveLeft = GetAsyncKeyState(0x41); // KEY A
	bool moveDown = GetAsyncKeyState(0x53); // KEY S
	bool moveRight = GetAsyncKeyState(0x44); // KEY D
	if (moveUp) {
		movePlayerInstructions(-1, 0, -1, 0, gameObjectConst::MoveDirectionState::UP);
	}
	if (moveDown) {
		movePlayerInstructions(1, 0, 1, 0, gameObjectConst::MoveDirectionState::DOWN);
	}
	if (moveLeft) {
		movePlayerInstructions(0, -1, 0, -1, gameObjectConst::MoveDirectionState::LEFT);
	}
	if (moveRight) {
		movePlayerInstructions(0, 1, 0, 1, gameObjectConst::MoveDirectionState::RIGHT);
	}
}
inline void movePlayerInstructions(int xOffset, int yOffset, int xOffsetBehind, int yOffsetBehind, gameObjectConst::MoveDirectionState dir) {
	glm::ivec3 position = player->getPosition3d();
	if (passabilityMap[position.x + xOffset][position.z + yOffset] == static_cast<int>(gameObjectConst::GameObjectType::EMPTY) && !player->isMoving()) {
		player->move(dir);
		passabilityMap[position.x + xOffset][position.z + yOffset] = static_cast<int>(gameObjectConst::GameObjectType::PLAYER);
		passabilityMap[position.x][position.z] = 0;
		gameObjects[position.x + xOffset][position.z + yOffset] = player;
		gameObjects[position.x][position.z] = nullptr;
	}
	else if (passabilityMap[position.x + xOffset][position.z + yOffset] == static_cast<int>(gameObjectConst::GameObjectType::LIGHT_OBJECT) && 
		passabilityMap[position.x + xOffset + xOffsetBehind][position.z + yOffset + yOffsetBehind] == static_cast<int>(gameObjectConst::GameObjectType::EMPTY) && !player->isMoving()) {
		gameObjects[position.x + xOffset][position.z + yOffset]->move(dir, (GLfloat)mapSize/3);
		player->move(dir);
		passabilityMap[position.x + xOffset + xOffsetBehind][position.z + yOffset + yOffsetBehind] = static_cast<int>(gameObjectConst::GameObjectType::LIGHT_OBJECT);
		passabilityMap[position.x + xOffset][position.z + yOffset] = static_cast<int>(gameObjectConst::GameObjectType::EMPTY);
		gameObjects[position.x + xOffset + xOffsetBehind][position.z + yOffset + yOffsetBehind] = gameObjects[position.x + xOffset][position.z + yOffset];
		gameObjects[position.x + xOffset][position.z + yOffset] = nullptr;
		passabilityMap[position.x + xOffset][position.z + yOffset] = static_cast<int>(gameObjectConst::GameObjectType::PLAYER);
		passabilityMap[position.x][position.z] = static_cast<int>(gameObjectConst::GameObjectType::EMPTY);
		gameObjects[position.x + xOffset][position.z + yOffset] = player;
		gameObjects[position.x][position.z] = nullptr;
	}
}
inline void outMap() {
	std::cout << std::endl;
	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++)
			std::cout << passabilityMap[i][j] << " ";
		std::cout << std::endl;
	}
}
void Simulation() {
	double simTimePassed = getSimTime();
	cameraSimulation(simTimePassed);
	gameObjectsSimulation(simTimePassed);
	movePlayer();
	glutPostRedisplay();
}