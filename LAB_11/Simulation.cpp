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
	if (player != nullptr)
		player->simulate(simulationTime);
	for (int i = 0; i < monsterCount; i++)
		if(monster[i] != nullptr)
			monster[i]->simulate(simulationTime);
	for (int i = 0; i < mapSize; i++)
		for (int j = 0; j < mapSize; j++)
			if (passabilityMap[i][j] == static_cast<int>(gameObjectConst::GameObjectType::LIGHT_OBJECT) && gameObjects[i][j] != nullptr)
				gameObjects[i][j]->simulate(simulationTime);
	if (bomb != nullptr) {
		bomb->simulate(simulationTime);
	}
}
inline void movePlayer() {
	bool moveUp = GetAsyncKeyState(0x57); // KEY W
	bool moveLeft = GetAsyncKeyState(0x41); // KEY A
	bool moveDown = GetAsyncKeyState(0x53); // KEY S
	bool moveRight = GetAsyncKeyState(0x44); // KEY D
	bool plantBomb = GetAsyncKeyState(VK_SPACE);
	if (player != nullptr) {
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
		if (bomb == nullptr) {
			if (plantBomb) {
				glm::ivec2 bombPosition = player->getPosition2d();
				bomb = gameObjectFactory.create(gameObjectConst::GameObjectType::BOMB, mapSize, bombPosition.x, 0.5, bombPosition.y);
				passabilityMap[bombPosition.x][bombPosition.y] = static_cast<int>(gameObjectConst::GameObjectType::BOMB);
				bomb->move(gameObjectConst::MoveDirectionState::WAIT, bombTimeout);
			}
		}
	}
}
inline void bombSimulation() {
	if (bomb != nullptr && !bomb->isMoving())
		bombTimeOverInstructions();
}
inline void bombTimeOverInstructions() {
	glm::ivec2 bombPosition = bomb->getPosition2d();
	bool hereIsWasblowupByDir[4] = { false,false,false,false };
	for (int i = 1; i <= 2; i++) {
		if ((bombPosition.y + i >= 0 && bombPosition.y + i <= mapSize) && !hereIsWasblowupByDir[0] &&
			passabilityMap[bombPosition.x][bombPosition.y + i] == static_cast<int>(gameObjectConst::GameObjectType::LIGHT_OBJECT)) {
			passabilityMap[bombPosition.x][bombPosition.y + i] = static_cast<int>(gameObjectConst::GameObjectType::EMPTY);
			gameObjects[bombPosition.x][bombPosition.y + i].reset();
			hereIsWasblowupByDir[0] = true;
		}
		else if ((bombPosition.y + i >= 0 && bombPosition.y + i <= mapSize) && !hereIsWasblowupByDir[0] &&
			(passabilityMap[bombPosition.x][bombPosition.y + i] == static_cast<int>(gameObjectConst::GameObjectType::BORDER_OBJECT) ||
				passabilityMap[bombPosition.x][bombPosition.y + i] == static_cast<int>(gameObjectConst::GameObjectType::HEAVY_OBJECT))) {
			hereIsWasblowupByDir[0] = true;
		}
		if ((bombPosition.x + i >= 0 && bombPosition.x + i <= mapSize) && !hereIsWasblowupByDir[1] &&
			passabilityMap[bombPosition.x + i][bombPosition.y] == static_cast<int>(gameObjectConst::GameObjectType::LIGHT_OBJECT)) {
			passabilityMap[bombPosition.x + i][bombPosition.y] = static_cast<int>(gameObjectConst::GameObjectType::EMPTY);
			gameObjects[bombPosition.x + i][bombPosition.y].reset();
			hereIsWasblowupByDir[1] = true;
		}
		else if ((bombPosition.x + i >= 0 && bombPosition.x + i <= mapSize) && !hereIsWasblowupByDir[0] &&
			(passabilityMap[bombPosition.x + i][bombPosition.y] == static_cast<int>(gameObjectConst::GameObjectType::BORDER_OBJECT) ||
				passabilityMap[bombPosition.x + i][bombPosition.y] == static_cast<int>(gameObjectConst::GameObjectType::HEAVY_OBJECT))) {
			hereIsWasblowupByDir[1] = true;
		}
		if ((bombPosition.y - i >= 0 && bombPosition.y - i <= mapSize) && !hereIsWasblowupByDir[2] &&
			passabilityMap[bombPosition.x][bombPosition.y - i] == static_cast<int>(gameObjectConst::GameObjectType::LIGHT_OBJECT)) {
			passabilityMap[bombPosition.x][bombPosition.y - i] = static_cast<int>(gameObjectConst::GameObjectType::EMPTY);
			gameObjects[bombPosition.x][bombPosition.y - i].reset();
			hereIsWasblowupByDir[2] = true;
		}
		else if ((bombPosition.y - i >= 0 && bombPosition.y - i <= mapSize) && !hereIsWasblowupByDir[3] &&
			(passabilityMap[bombPosition.x][bombPosition.y - i] == static_cast<int>(gameObjectConst::GameObjectType::BORDER_OBJECT) ||
				passabilityMap[bombPosition.x][bombPosition.y - i] == static_cast<int>(gameObjectConst::GameObjectType::HEAVY_OBJECT))) {
			hereIsWasblowupByDir[2] = true;
		}
		if ((bombPosition.x - i >= 0 && bombPosition.x - i <= mapSize) && !hereIsWasblowupByDir[3] &&
			passabilityMap[bombPosition.x - i][bombPosition.y] == static_cast<int>(gameObjectConst::GameObjectType::LIGHT_OBJECT)) {
			passabilityMap[bombPosition.x - i][bombPosition.y] = static_cast<int>(gameObjectConst::GameObjectType::EMPTY);
			gameObjects[bombPosition.x - i][bombPosition.y].reset();
			hereIsWasblowupByDir[3] = true;
		}
		else if ((bombPosition.x - i >= 0 && bombPosition.x - i <= mapSize) && !hereIsWasblowupByDir[0] &&
			(passabilityMap[bombPosition.x - i][bombPosition.y] == static_cast<int>(gameObjectConst::GameObjectType::BORDER_OBJECT) ||
				passabilityMap[bombPosition.x - i][bombPosition.y] == static_cast<int>(gameObjectConst::GameObjectType::HEAVY_OBJECT))) {
			hereIsWasblowupByDir[3] = true;
		}
	}
	for (int i = 0; i <= 2; i++) {
		for (int j = 0; j < monsterCount; j++) {
			if (monster[j] != nullptr) {
				glm::ivec2 monsterPosition = monster[j]->getPosition2d();
				if (bombPosition.x == monsterPosition.x && bombPosition.y + i == monsterPosition.y && !hereIsWasblowupByDir[0]) {
					monster[j].reset();
					hereIsWasblowupByDir[0] = true;
				}
				if (bombPosition.x + i == monsterPosition.x && bombPosition.y == monsterPosition.y && !hereIsWasblowupByDir[1]) {
					monster[j].reset();
					hereIsWasblowupByDir[1] = true;
				}
				if (bombPosition.x == monsterPosition.x && bombPosition.y - i == monsterPosition.y && !hereIsWasblowupByDir[2]) {
					monster[j].reset();
					hereIsWasblowupByDir[2] = true;
				}
				if (bombPosition.x - i == monsterPosition.x && bombPosition.y == monsterPosition.y && !hereIsWasblowupByDir[3]) {
					monster[j].reset();
					hereIsWasblowupByDir[3] = true;

				}
			}
		}
		if (player != nullptr) {
			glm::ivec2 playerPosition = player->getPosition2d();
			if (bombPosition.x == playerPosition.x && bombPosition.y + i == playerPosition.y && !hereIsWasblowupByDir[0]) {
				player.reset();
				hereIsWasblowupByDir[0] = true;
			}
			if (bombPosition.x + i == playerPosition.x && bombPosition.y == playerPosition.y && !hereIsWasblowupByDir[1]) {
				player.reset();
				hereIsWasblowupByDir[1] = true;
			}
			if (bombPosition.x == playerPosition.x && bombPosition.y - i == playerPosition.y && !hereIsWasblowupByDir[2]) {
				player.reset();
				hereIsWasblowupByDir[2] = true;
			}
			if (bombPosition.x - i == playerPosition.x && bombPosition.y == playerPosition.y && !hereIsWasblowupByDir[3]) {
				player.reset();
				hereIsWasblowupByDir[3] = true;
			}
		}
	}
	passabilityMap[bombPosition.x][bombPosition.y] = static_cast<int>(gameObjectConst::GameObjectType::EMPTY);
	bombAfterBlowup(bombPosition);
	bomb.reset();
}
inline void movePlayerInstructions(int xOffset, int yOffset, int xOffset2nd, int yOffset2nd, gameObjectConst::MoveDirectionState dir) {
	if (player != nullptr) {
		glm::ivec3 position = player->getPosition3d();
		if (passabilityMap[position.x + xOffset][position.z + yOffset] == static_cast<int>(gameObjectConst::GameObjectType::EMPTY) && !player->isMoving()) {
			player->move(dir, 6.0f);
		}
		else if (passabilityMap[position.x + xOffset][position.z + yOffset] == static_cast<int>(gameObjectConst::GameObjectType::LIGHT_OBJECT) &&
			passabilityMap[position.x + xOffset + xOffset2nd][position.z + yOffset + yOffset2nd] == static_cast<int>(gameObjectConst::GameObjectType::EMPTY) && !player->isMoving()) {
			for (int i = 0; i < monsterCount; i++) {
				if (monster[i] != nullptr) {
					glm::ivec3 monsterPos = monster[i]->getPosition3d();
					if (monsterPos.x - xOffset - xOffset2nd == position.x && monsterPos.z - yOffset - yOffset2nd == position.z) {
						return;
					}
				}
			}
			gameObjects[position.x + xOffset][position.z + yOffset]->move(dir, (GLfloat)mapSize / 3);
			player->move(dir, 6.0f);
			passabilityMap[position.x + xOffset + xOffset2nd][position.z + yOffset + yOffset2nd] = static_cast<int>(gameObjectConst::GameObjectType::LIGHT_OBJECT);
			passabilityMap[position.x + xOffset][position.z + yOffset] = static_cast<int>(gameObjectConst::GameObjectType::EMPTY);
			gameObjects[position.x + xOffset + xOffset2nd][position.z + yOffset + yOffset2nd] = gameObjects[position.x + xOffset][position.z + yOffset];
			gameObjects[position.x + xOffset][position.z + yOffset] = nullptr;
			std::swap(passabilityMap[position.x][position.z], passabilityMap[position.x + xOffset][position.z + yOffset]);
		}
		for (int i = 0; i < monsterCount; i++) {
			if (monster[i] != nullptr) {
				glm::ivec3 monsterPos = monster[i]->getPosition3d();
				if (monsterPos.x == position.x && monsterPos.z == position.z) {
					player->setGraphicObject(GraphicObject());
					player.reset();
					break;
				}
			}
		}
	}
}
inline void moveMonster(std::shared_ptr<GameObject> & monsterObj, std::mt19937 & mersenneRand) {
	if (monsterObj != nullptr) {
		if (!monsterObj->isMoving()) {
			glm::ivec2 offset;
			glm::ivec3 position = monsterObj->getPosition3d();
			gameObjectConst::MoveDirectionState dir;
			if (monsterObj->getPrevState() != gameObjectConst::MoveDirectionState::STOP) {
				dir = monsterObj->getPrevState();
				offset = getOffset(dir);
			}
			else {
				std::vector<gameObjectConst::MoveDirectionState> possibleDirs;
				int countOfPossibleDirs = 0;
				for (int i = 1; i <= 4; i++) {
					dir = static_cast<gameObjectConst::MoveDirectionState>(i);
					offset = getOffset(dir);
					if (passabilityMap[position.x + offset.x][position.z + offset.y] == static_cast<int>(gameObjectConst::GameObjectType::EMPTY)) {
						possibleDirs.push_back(dir);
						countOfPossibleDirs += 1;
					}
				}
				if (possibleDirs.size() <= 0) {
					monsterObj.reset();
					return;
				}
				dir = possibleDirs[mersenneRand() % countOfPossibleDirs];
				offset = getOffset(dir);
			}
			if (monsterObj->getPrevState() != gameObjectConst::MoveDirectionState::STOP) {
				if (passabilityMap[position.x + offset.x][position.z + offset.y] == static_cast<int>(gameObjectConst::GameObjectType::EMPTY) &&
					passabilityMap[position.x + offset.y][position.z + offset.x] == static_cast<int>(gameObjectConst::GameObjectType::EMPTY) &&
					passabilityMap[position.x - offset.y][position.z - offset.x] == static_cast<int>(gameObjectConst::GameObjectType::EMPTY)) {
					std::vector<gameObjectConst::MoveDirectionState> possibleDirs;
					std::vector<gameObjectConst::MoveDirectionState> wrongDirs = { getDir(glm::ivec2(-offset.x,-offset.y)) };
					possibleDirs = getPossibleDirs(wrongDirs);
					dir = possibleDirs[mersenneRand() % 3];
				}
				else if (passabilityMap[position.x + offset.x][position.z + offset.y] == static_cast<int>(gameObjectConst::GameObjectType::EMPTY) &&
					passabilityMap[position.x + offset.y][position.z + offset.x] == static_cast<int>(gameObjectConst::GameObjectType::EMPTY) &&
					passabilityMap[position.x - offset.y][position.z - offset.x] != static_cast<int>(gameObjectConst::GameObjectType::EMPTY)) {
					std::vector<gameObjectConst::MoveDirectionState> possibleDirs;
					std::vector<gameObjectConst::MoveDirectionState> wrongDirs = { getDir(glm::ivec2(-offset.x,-offset.y)), getDir(glm::ivec2(-offset.y,-offset.x)) };
					possibleDirs = getPossibleDirs(wrongDirs);
					dir = possibleDirs[mersenneRand() % 2];
				}
				else if (passabilityMap[position.x + offset.x][position.z + offset.y] == static_cast<int>(gameObjectConst::GameObjectType::EMPTY) &&
					passabilityMap[position.x + offset.y][position.z + offset.x] != static_cast<int>(gameObjectConst::GameObjectType::EMPTY) &&
					passabilityMap[position.x - offset.y][position.z - offset.x] == static_cast<int>(gameObjectConst::GameObjectType::EMPTY)) {
					std::vector<gameObjectConst::MoveDirectionState> possibleDirs;
					std::vector<gameObjectConst::MoveDirectionState> wrongDirs = { getDir(glm::ivec2(-offset.x,-offset.y)), getDir(glm::ivec2(offset.y,offset.x)) };
					possibleDirs = getPossibleDirs(wrongDirs);
					dir = possibleDirs[mersenneRand() % 2];
				}
				else if (passabilityMap[position.x + offset.x][position.z + offset.y] != static_cast<int>(gameObjectConst::GameObjectType::EMPTY) &&
					passabilityMap[position.x + offset.y][position.z + offset.x] != static_cast<int>(gameObjectConst::GameObjectType::EMPTY) &&
					passabilityMap[position.x - offset.y][position.z - offset.x] == static_cast<int>(gameObjectConst::GameObjectType::EMPTY)) {
					dir = getDir(glm::ivec2(-offset.y, -offset.x));
				}
				else if (passabilityMap[position.x + offset.x][position.z + offset.y] != static_cast<int>(gameObjectConst::GameObjectType::EMPTY) &&
					passabilityMap[position.x + offset.y][position.z + offset.x] == static_cast<int>(gameObjectConst::GameObjectType::EMPTY) &&
					passabilityMap[position.x - offset.y][position.z - offset.x] != static_cast<int>(gameObjectConst::GameObjectType::EMPTY)) {
					dir = getDir(glm::ivec2(offset.y, offset.x));
				}
				else if (passabilityMap[position.x + offset.x][position.z + offset.y] != static_cast<int>(gameObjectConst::GameObjectType::EMPTY) &&
					(passabilityMap[position.x + offset.y][position.z + offset.x] == static_cast<int>(gameObjectConst::GameObjectType::EMPTY) ||
						passabilityMap[position.x - offset.y][position.z - offset.x] == static_cast<int>(gameObjectConst::GameObjectType::EMPTY))) {
					std::vector<gameObjectConst::MoveDirectionState> possibleDirs;
					std::vector<gameObjectConst::MoveDirectionState> wrongDirs = { getDir(glm::ivec2(offset.x,offset.y)), getDir(glm::ivec2(-offset.x,-offset.y)) };
					possibleDirs = getPossibleDirs(wrongDirs);
					dir = possibleDirs[mersenneRand() % 2];
				}
				else if (passabilityMap[position.x + offset.x][position.z + offset.y] != static_cast<int>(gameObjectConst::GameObjectType::EMPTY) &&
					passabilityMap[position.x - offset.x][position.z - offset.y] != static_cast<int>(gameObjectConst::GameObjectType::EMPTY) &&
					passabilityMap[position.x + offset.y][position.z + offset.x] != static_cast<int>(gameObjectConst::GameObjectType::EMPTY) &&
					passabilityMap[position.x - offset.y][position.z - offset.x] != static_cast<int>(gameObjectConst::GameObjectType::EMPTY)) {
					return;
				}
				else if ((passabilityMap[position.x + offset.x][position.z + offset.y] != static_cast<int>(gameObjectConst::GameObjectType::EMPTY) &&
					passabilityMap[position.x + offset.y][position.z + offset.x] != static_cast<int>(gameObjectConst::GameObjectType::EMPTY) &&
					passabilityMap[position.x - offset.y][position.z - offset.x] != static_cast<int>(gameObjectConst::GameObjectType::EMPTY)) &&
					(passabilityMap[position.x - offset.x][position.z - offset.y] == static_cast<int>(gameObjectConst::GameObjectType::EMPTY))) {
					switch (dir) {
					case gameObjectConst::MoveDirectionState::UP: dir = gameObjectConst::MoveDirectionState::DOWN; break;
					case gameObjectConst::MoveDirectionState::DOWN: dir = gameObjectConst::MoveDirectionState::UP; break;
					case gameObjectConst::MoveDirectionState::LEFT: dir = gameObjectConst::MoveDirectionState::RIGHT; break;
					case gameObjectConst::MoveDirectionState::RIGHT: dir = gameObjectConst::MoveDirectionState::LEFT; break;
					}
				}
				offset = getOffset(dir);
			}
			if (passabilityMap[position.x + offset.x][position.z + offset.y] == static_cast<int>(gameObjectConst::GameObjectType::EMPTY)) {
				if (player != nullptr) {
					glm::ivec3 playerPosition = player->getPosition3d();
					if ((playerPosition.x - offset.x == position.x && playerPosition.z - offset.y == position.z)) {
						player->setGraphicObject(GraphicObject());
						player.reset();
					}
				}
				monsterObj->setPrevState(dir);
				monsterObj->move(dir, 3.0f);
			}
		}
	}
}
inline glm::ivec2 getOffset(gameObjectConst::MoveDirectionState dir) {
	glm::ivec2 offset = glm::ivec2(0.0, 0.0);
	switch (dir) {
	case gameObjectConst::MoveDirectionState::UP: {
		offset.x = -1;
		offset.y = 0;
	}; break;
	case gameObjectConst::MoveDirectionState::DOWN: {
		offset.x = 1;
		offset.y = 0;
	}; break;
	case gameObjectConst::MoveDirectionState::LEFT: {
		offset.x = 0;
		offset.y = -1;
	}; break;
	case gameObjectConst::MoveDirectionState::RIGHT: {
		offset.x = 0;
		offset.y = 1;
	}; break;
	}
	return offset;
}
inline gameObjectConst::MoveDirectionState getDir(glm::ivec2 offset) {
	gameObjectConst::MoveDirectionState dir = gameObjectConst::MoveDirectionState::STOP;
	if (offset == glm::ivec2(-1, 0))
		dir = gameObjectConst::MoveDirectionState::UP;
	else if (offset == glm::ivec2(1, 0))
		dir = gameObjectConst::MoveDirectionState::DOWN;
	else if (offset == glm::ivec2(0, -1))
		dir = gameObjectConst::MoveDirectionState::LEFT;
	else if (offset == glm::ivec2(0, 1))
		dir = gameObjectConst::MoveDirectionState::RIGHT;
	return dir;
}
inline void outMap() {
	std::cout << std::endl;
	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++)
			std::cout << passabilityMap[i][j] << " ";
		std::cout << std::endl;
	}
}
inline std::vector<gameObjectConst::MoveDirectionState> getPossibleDirs(std::vector<gameObjectConst::MoveDirectionState> & wrongDirs) {
	std::vector<gameObjectConst::MoveDirectionState> possibleDirs;
	for (int i = 1; i <= 4; i++)
		if (std::find(wrongDirs.begin(), wrongDirs.end(), static_cast<gameObjectConst::MoveDirectionState>(i)) == wrongDirs.end())
			possibleDirs.push_back(static_cast<gameObjectConst::MoveDirectionState>(i));
	return possibleDirs;
}
void Simulation() {
	double simTimePassed = getSimTime();
	cameraSimulation(simTimePassed);
	gameObjectsSimulation(simTimePassed);
	movePlayer();
	bombSimulation();
	for (int i = 0; i < monsterCount; i++) {
		std::mt19937 randSeed(time(NULL) + static_cast<time_t>(i));
		moveMonster(monster[i],randSeed);
	}
	glutPostRedisplay();
}