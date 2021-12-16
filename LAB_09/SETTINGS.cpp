#include "SETTINGS.h"
namespace PROJECT_SETTINGS {
	namespace TEXTURE {
		FILTER FILTER_VALUE;
		GLenum FILTER_MODE, FILTER_MIPMAP_MODE;
		GLfloat FILTER_ANISOTROPIC_VALUE;
		void setFiltrationMode(FILTER filter) {
			switch (filter) {
			case FILTER::POINT: {
				FILTER_MODE = GL_NEAREST;
				FILTER_MIPMAP_MODE = GL_NEAREST_MIPMAP_NEAREST;
			}; break;
			case FILTER::BILINEAR: {
				FILTER_MODE = GL_LINEAR;
				FILTER_MIPMAP_MODE = GL_LINEAR_MIPMAP_NEAREST;
			}; break;
			case FILTER::TRILINEAR: {
				FILTER_MODE = GL_LINEAR;
				FILTER_MIPMAP_MODE = GL_LINEAR_MIPMAP_LINEAR;
			}; break;
			case FILTER::ANISOTROPIC: {
				FILTER_MODE = GL_TEXTURE_MAX_ANISOTROPY_EXT;

			}; break;
			default: {
				FILTER_MODE = GL_NEAREST;
				FILTER_MIPMAP_MODE = GL_NEAREST_MIPMAP_NEAREST;
			}; break;
			}
		}
		void setAnisotropicValue(GLfloat fValue) {
			GLfloat tempF;
			glGetFloatv(GL_TEXTURE_MAX_ANISOTROPY_EXT, &tempF);
			if (fValue > tempF)
				FILTER_ANISOTROPIC_VALUE = tempF;
			else
				FILTER_ANISOTROPIC_VALUE = fValue;
		}
		void init(FILTER filter, GLfloat anisotropicValue) {
			setFiltrationMode(filter);
			setAnisotropicValue(anisotropicValue);
		}
		void setDefault() {
			init(FILTER::TRILINEAR, 1.0f);
		}
	}
}