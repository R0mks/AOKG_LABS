#include "Material.h"

PhongMaterial::PhongMaterial()
{
}

void PhongMaterial::setAmbient(glm::vec4 color)
{
	this->ambient = color;
}

void PhongMaterial::setDiffuse(glm::vec4 color)
{
	this->diffuse = color;
}

void PhongMaterial::setSpecular(glm::vec4 color)
{
	this->specular = color;
}

void PhongMaterial::setEmission(glm::vec4 color)
{
	this->emission = color;
}

void PhongMaterial::setShininess(GLfloat param)
{
	this->shininess = param;
}

void PhongMaterial::load(std::string fileName)
{
	setlocale(LC_ALL, "ru");

	std::ifstream fin;
	fin.open(fileName);

	if (fin.is_open())
	{
		std::string str;
		GLfloat numbers[4];

		while (fin >> str)
		{
			if (str == "diffuse:")
			{
				fin >> numbers[0];
				fin >> numbers[1];
				fin >> numbers[2];
				fin >> numbers[3];

				this->setDiffuse(glm::vec4(numbers[0], numbers[1], numbers[2], numbers[3]));

			}
			if (str == "ambient:")
			{
				fin >> numbers[0];
				fin >> numbers[1];
				fin >> numbers[2];
				fin >> numbers[3];

				this->setAmbient(glm::vec4(numbers[0], numbers[1], numbers[2], numbers[3]));
			}
			if (str == "specular:")
			{
				fin >> numbers[0];
				fin >> numbers[1];
				fin >> numbers[2];
				fin >> numbers[3];

				this->setSpecular(glm::vec4(numbers[0], numbers[1], numbers[2], numbers[3]));
			}
			if (str == "emission:")
			{
				fin >> numbers[0];
				fin >> numbers[1];
				fin >> numbers[2];
				fin >> numbers[3];

				this->setEmission(glm::vec4(numbers[0], numbers[1], numbers[2], numbers[3]));
			}
			if (str == "shininess:")
			{
				fin >> numbers[0];

				this->setShininess(numbers[0]);
			}
		}
	}

	fin.close();
}

void PhongMaterial::apply()
{
	GLfloat ambient[] = { this->ambient[0], this->ambient[1], this->ambient[2], this->ambient[3] };
	GLfloat diffuse[] = { this->diffuse[0], this->diffuse[1], this->diffuse[2], this->diffuse[3] };
	GLfloat specular[] = { this->specular[0], this->specular[1], this->specular[2], this->specular[3] };
	GLfloat emission[] = { this->emission[0], this->emission[1], this->emission[2], this->emission[3] };

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glMaterialf(GL_FRONT, GL_SHININESS, this->shininess);
}

PhongMaterialWithTexture::PhongMaterialWithTexture()
{
}

void PhongMaterialWithTexture::setAmbient(glm::vec4 color)
{
	this->ambient = color;
}

void PhongMaterialWithTexture::setDiffuse(glm::vec4 color)
{
	this->diffuse = color;
}

void PhongMaterialWithTexture::setSpecular(glm::vec4 color)
{
	this->specular = color;
}

void PhongMaterialWithTexture::setEmission(glm::vec4 color)
{
	this->emission = color;
}

void PhongMaterialWithTexture::setShininess(GLfloat param)
{
	this->shininess = param;
}

void PhongMaterialWithTexture::load(std::string fileName)
{
	setlocale(LC_ALL, "ru");

	std::ifstream fin;
	fin.open(fileName);

	if (fin.is_open())
	{
		std::string str;
		GLfloat numbers[4];

		while (fin >> str)
		{
			if (str == "diffuse:")
			{
				fin >> numbers[0];
				fin >> numbers[1];
				fin >> numbers[2];
				fin >> numbers[3];

				this->setDiffuse(glm::vec4(numbers[0], numbers[1], numbers[2], numbers[3]));

			}
			if (str == "ambient:")
			{
				fin >> numbers[0];
				fin >> numbers[1];
				fin >> numbers[2];
				fin >> numbers[3];

				this->setAmbient(glm::vec4(numbers[0], numbers[1], numbers[2], numbers[3]));
			}
			if (str == "specular:")
			{
				fin >> numbers[0];
				fin >> numbers[1];
				fin >> numbers[2];
				fin >> numbers[3];

				this->setSpecular(glm::vec4(numbers[0], numbers[1], numbers[2], numbers[3]));
			}
			if (str == "emission:")
			{
				fin >> numbers[0];
				fin >> numbers[1];
				fin >> numbers[2];
				fin >> numbers[3];

				this->setEmission(glm::vec4(numbers[0], numbers[1], numbers[2], numbers[3]));
			}
			if (str == "shininess:")
			{
				fin >> numbers[0];

				this->setShininess(numbers[0]);
			}
		}
	}

	fin.close();
}

void PhongMaterialWithTexture::apply()
{
	GLfloat ambient[] = { this->ambient[0], this->ambient[1], this->ambient[2], this->ambient[3] };
	GLfloat diffuse[] = { this->diffuse[0], this->diffuse[1], this->diffuse[2], this->diffuse[3] };
	GLfloat specular[] = { this->specular[0], this->specular[1], this->specular[2], this->specular[3] };
	GLfloat emission[] = { this->emission[0], this->emission[1], this->emission[2], this->emission[3] };

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glMaterialf(GL_FRONT, GL_SHININESS, this->shininess);

	if (this->texture != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		this->texture.get()->apply();
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
	else
	{
		Texture::disableAll;
	}
}

void PhongMaterialWithTexture::setTexture(std::shared_ptr<Texture> texture)
{
	this->texture = texture;
}
