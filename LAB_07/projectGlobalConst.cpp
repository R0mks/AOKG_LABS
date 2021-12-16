#include "projectGlobalConst.h"
namespace lightConst {
	const char* lightType[6]{
		"AMBIENT:", "DIFFUSE:", "SPECULAR:", "EMISSION:", "SHININESS:", "POSITION:"
	};
	const char* phongMaterialExtension = "phmat";
}
namespace meshConst {
	const char* modelType[4]{
		"v", "vn", "vt", "f"
	};
	const char* modelExtension = "obj";
}
namespace msg{
	namespace error {
		const char* fileFirstPartTemplate = "Файл";
		const char* fileErrListMessageTemplates[2] = {
			"повреждён!",
			"не может быть открыт или создан! Проверьте правильность введёных данных!"
		};
		void outErrMessage(std::string& const filename, errType num) {
			std::cout << "\n" << fileFirstPartTemplate << " " << filename << " ";
			switch (num) {
			case errType::FILE_BROKEN: 
				std::cout << fileErrListMessageTemplates[0];
				break;
			case errType::FILE_NOT_EXIST: 
				std::cout << fileErrListMessageTemplates[1];
				break;
			default: return; break;
			}
		}
		void outErrMessage(std::string& const filename, errType num, std::exception& exception) {
			outErrMessage(filename, num);
			std::cout << "\n" << exception.what();
		}
	}
}