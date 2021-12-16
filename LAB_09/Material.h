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

// ����� ��� ������ � ����������
class PhongMaterialWithTexture : public Material
{
public:
	// ����������� �� ���������
	PhongMaterialWithTexture();
	// ������� ���������� ���������
	void setAmbient(glm::vec4 color);
	void setDiffuse(glm::vec4 color);
	void setSpecular(glm::vec4 color);
	void setEmission(glm::vec4 color);
	void setShininess(float p);
	// ��������� ������������ ��������
	void setTexture(std::shared_ptr<Texture> texture);
	// �������� ���������� ��������� �� �������� ���������� �����
	void load(std::string filename);
	// ��������� ���� ���������� ���������
	void apply();
private:
	// ������� ������������ 
	glm::vec4 ambient;
	// ��������� ������������
	glm::vec4 diffuse;
	// ���������� ������������
	glm::vec4 specular;
	// ������������
	glm::vec4 emission;
	// ������� ����������������
	float shininess;
	// ������������ ��������
	std::shared_ptr<Texture> texture;
};
