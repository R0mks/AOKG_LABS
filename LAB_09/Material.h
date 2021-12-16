#pragma once

#include <Windows.h>
#include <stdio.h>

#include "glew-2.2.0/include/GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"

#include <iostream>
#include <string>
#include <fstream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Texture.h"

class Material
{
public:
	virtual void apply(void) = 0;
};

class PhongMaterial : public Material
{
public:
	PhongMaterial();

	void setAmbient(glm::vec4 color);
	void setDiffuse(glm::vec4 color);
	void setSpecular(glm::vec4 color);
	void setEmission(glm::vec4 color);
	void setShininess(GLfloat param);

	void load(std::string fileName);
	
	void apply();

private:
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	glm::vec4 emission;
	GLfloat shininess;
};

// КЛАСС ДЛЯ РАБОТЫ С МАТЕРИАЛОМ
class PhongMaterialWithTexture : public Material
{
public:
	// конструктор по умолчанию
	PhongMaterialWithTexture();
	// задание параметров материала
	void setAmbient(glm::vec4 color);
	void setDiffuse(glm::vec4 color);
	void setSpecular(glm::vec4 color);
	void setEmission(glm::vec4 color);
	void setShininess(float p);
	// установка используемой текстуры
	void setTexture(std::shared_ptr<Texture> texture);
	// загрузка параметров материала из внешнего текстового файла
	void load(std::string filename);
	// установка всех параметров материала
	void apply();
private:
	// фоновая составляющая 
	glm::vec4 ambient;
	// диффузная составялющая
	glm::vec4 diffuse;
	// зеркальная составляющая
	glm::vec4 specular;
	// самосвечение
	glm::vec4 emission;
	// степень отполированности
	float shininess;
	// используемая текстура
	std::shared_ptr<Texture> texture;
};
