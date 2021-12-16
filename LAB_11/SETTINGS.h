#ifndef SETTINGS_H
#define SETTINGS_H
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
namespace PROJECT_SETTINGS {
	namespace TEXTURE {
		enum class FILTER {
			POINT,
			BILINEAR,
			TRILINEAR,
			ANISOTROPIC
		};
		extern FILTER FILTER_VALUE;
		extern GLenum FILTER_MODE, FILTER_MIPMAP_MODE;
		extern GLfloat FILTER_ANISOTROPIC_VALUE;
		extern void setFiltrationMode(FILTER filter);
		extern void setAnisotropicValue(GLfloat fValue);
		extern void init(FILTER filter = FILTER::TRILINEAR, GLfloat anisotropicValue = 1.0f);
		extern void setDefault();
	}
	extern int MAX_DECALES_COUNT;
};
#endif // !SETTINGS_H