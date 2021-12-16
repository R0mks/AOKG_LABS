#include "Decal.h"
Decal::Decal(glm::vec2 pos, int mapSize) {
	setPosition(pos, mapSize);
	graphicObject.setMesh(mesh);
	graphicObject.setLightMaterial(material);
}
void Decal::init(std::string currentDirectoryPath) {
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	texture->load(currentDirectoryPath + "\\data\\textures\\decals\\bomb_crater.png");
	material = std::make_shared<PhongMaterialWithTexture>();
	material->load(currentDirectoryPath + "\\data\\materials\\DecalMaterial.phmat");
	material->setTexture(texture);
	mesh = std::make_shared<Mesh>();
	mesh->load(currentDirectoryPath + "\\data\\meshes\\Decal.obj");
}
void Decal::setPosition(glm::vec2 pos, int mapSize) {
	position = pos;
	graphicObject.setRotateAngle(glm::vec3(0.0, -90.0, 0.0));
	graphicObject.setSize(glm::vec3(-1.0, 1.0, 1.0));
	graphicObject.setPosition(glm::vec3(pos.x - mapSize / 2, 0.0, pos.y - mapSize / 2));
	graphicObject.setRotateAngle(glm::vec3(0.0, 90.0, 0.0));
	graphicObject.setSize(glm::vec3(1.0, 1.0, -1.0));
}
glm::vec2 Decal::getPosition() {
	return position;
}
void Decal::draw() {
	glEnable(GL_POLYGON_OFFSET_FILL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonOffset(-1, -3);
	graphicObject.draw();
	glDisable(GL_BLEND);
	glDisable(GL_POLYGON_OFFSET_FILL);
}
std::shared_ptr<PhongMaterialWithTexture> Decal::material = nullptr;
std::shared_ptr<Mesh> Decal::mesh = nullptr;