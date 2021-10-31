#ifndef PROJECTGLOBALCONSTDATA_H
#define PROJECTGLOBALCONSTDATA_H
#include <string>
namespace lightConst {
	enum class colorType {
		NULLCLR = 0, AMBIENT, DIFUSE, SPECULAR, EMISSION, SHININESS, POSITION
	};
	extern const char* lightType[6];
	extern const char* phongMaterialExtension;
}
#endif
