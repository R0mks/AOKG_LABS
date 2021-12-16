#include "globalFunctions.h"
namespace addFns {
	void fillMapObjects(int (&mapIndexes)[rows][cols], std::shared_ptr<GameObject> (&mapObjects)[rows][cols], int size, std::map<int, std::shared_ptr<GraphicObject>>& pattern) {
		for(int i = 0; i < size; i++)
			for (int j = 0; j < size; j++) {
				for (auto k = pattern.begin(); k != pattern.end(); *k++) {
					if (k->first == mapIndexes[i][j]) {
						mapObjects[i][j] = std::shared_ptr<GameObject>(new GameObject());
						mapObjects[i][j]->setGraphicObject(k->second);
						mapObjects[i][j]->setPosition(glm::ivec2(i, j));
						break;
					}
				}
			}
	}
}