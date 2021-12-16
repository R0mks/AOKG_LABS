#ifndef ADDITIONAL_FNS_H
#define ADDITIONAL_FNS_H
#include <GLM/glm.hpp>
#include <map>
#include "GraphicObject.h"
#include "GameObject.h"
namespace addFns {
	template<int rows, int cols>
	extern void fillMapObjects(int(&mapIndexes)[rows][cols], std::shared_ptr<GameObject>(&mapObjects)[rows][cols], int size, std::map<int, GraphicObject> pattern) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				for (auto k = pattern.begin(); k != pattern.end(); *k++) {
					if (mapIndexes[i][j] == (*k).first + 1) {
						mapObjects[i][j] = std::shared_ptr<GameObject>(new GameObject());
						mapObjects[i][j]->setGraphicObject((*k).second);
						mapObjects[i][j]->setPosition(glm::vec2(i - size / 2, j - size / 2));
					}
				}
			}
		}
	}
}
#endif