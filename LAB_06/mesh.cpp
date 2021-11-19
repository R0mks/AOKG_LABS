#include "Mesh.h"
#include "globalFunctions.h"
#include <fstream>
#include <sstream>
#include <GLM/gtc/type_ptr.hpp>
Mesh::Mesh() {

};
Mesh::~Mesh() {
	vertices.clear();
};
void Mesh::load(std::string fileNameFullPath) {
	std::vector<glm::vec3> vts;
	std::vector<glm::vec3> nms;
	std::vector<glm::vec3> txs;
	std::vector<glm::ivec3> fPoints;
	std::string buffStringL1;
	std::ifstream meshData(fileNameFullPath.c_str(), std::ios_base::in);
	if (meshData.is_open()) {
		meshData.exceptions(std::ifstream::badbit);
		try {
			while (std::getline(meshData, buffStringL1)) {
				std::istringstream stringStream1(buffStringL1, std::ios_base::in);
				std::string buffStringL2;
				while (stringStream1 >> buffStringL2) {
					switch (getStringCode(buffStringL2)) {
					case meshConst::modelTypeCode::VERTICE: {
						vts.push_back(dataToVec::getVec3FromFile(stringStream1));
					}; break;
					case meshConst::modelTypeCode::NORMALE: {
						nms.push_back(dataToVec::getVec3FromFile(stringStream1));
					}; break;
					case meshConst::modelTypeCode::TEXTURE: {
						txs.push_back(dataToVec::getVec3FromFile(stringStream1));
					}; break;
					case meshConst::modelTypeCode::POLYGON: {
						for (int i = 0; i < 3; i++) {
							fPoints.push_back(getPolygonDataFromFile(stringStream1));
						}
					}; break;
					}
					buffStringL2.clear();
				}
				stringStream1.str(std::string());
				buffStringL1.clear();
			}
			for (auto element = fPoints.begin(); element != fPoints.end(); *element++) {
				vertices.push_back(meshConst::Vertex(vts[element->x-1],txs[element->y-1],nms[element->z-1]));
			}
		}
		catch (std::exception e) {
			msg::error::outErrMessage(fileNameFullPath, msg::error::errType::FILE_BROKEN, e);
		}
	}
	else {
		msg::error::outErrMessage(fileNameFullPath, msg::error::errType::FILE_NOT_EXIST);
	}
	if(!vts.empty()) vts.clear();
	if (!nms.empty()) nms.clear();
	if (!txs.empty()) txs.clear();
	if (!fPoints.empty()) fPoints.clear();
	meshData.close();
};
void Mesh::draw() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	const size_t strideValue = sizeof(meshConst::Vertex);
	glVertexPointer(3, GL_FLOAT, strideValue, &vertices[0].coordinates);
	glTexCoordPointer(3, GL_FLOAT, strideValue, &vertices[0].textureCoordinates);
	glNormalPointer(GL_FLOAT, strideValue, &vertices[0].normalCoordinates);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
};
glm::ivec3 Mesh::getPolygonDataFromFile(std::ifstream& file) {
	int fElement[3];
	size_t pos = 0;
	std::string buffString;
	std::string delimiter = "/";
	int token, i = 0;
	file >> buffString;
	while (((pos = buffString.find(delimiter)) != std::string::npos)) {
		token = std::stoi(buffString.substr(0, pos));
		fElement[i++] = token;
		buffString.erase(0, pos + delimiter.length());
	}
	fElement[i] = std::stoi(buffString);
	return glm::ivec3(fElement[0], fElement[1], fElement[2]);
}
glm::ivec3 Mesh::getPolygonDataFromFile(std::istringstream& stringStream) {
	int fElement[3];
	size_t pos = 0;
	std::string buffString;
	std::string delimiter = "/";
	int token, i = 0;
	stringStream >> buffString;
	while (((pos = buffString.find(delimiter)) != std::string::npos)) {
		token = std::stoi(buffString.substr(0, pos));
		fElement[i++] = token;
		buffString.erase(0, pos + delimiter.length());
	}
	fElement[i] = std::stoi(buffString);
	return glm::ivec3(fElement[0], fElement[1], fElement[2]);
}
meshConst::modelTypeCode Mesh::getStringCode(std::string const& strData) {
	if (strData == meshConst::modelType[0])
		return meshConst::modelTypeCode::VERTICE;
	if (strData == meshConst::modelType[1])
		return meshConst::modelTypeCode::NORMALE;
	if (strData == meshConst::modelType[2])
		return meshConst::modelTypeCode::TEXTURE;
	if (strData == meshConst::modelType[3])
		return meshConst::modelTypeCode::POLYGON;
	return static_cast<meshConst::modelTypeCode>(0);
};