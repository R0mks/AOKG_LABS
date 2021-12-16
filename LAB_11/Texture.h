#ifndef TEXTURE_H
#define TEXTURE_H
#include <GL/glew.h>

#include <GL/freeglut.h>

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include "projectGlobalConst.h"
#include <string>
class Texture {
public:
	Texture();
	~Texture();
	void load(std::string filename);
	void apply();
	static void disableAll();
private:
	GLuint textureId;
};
#endif

