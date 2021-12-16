#include "Texture.h";
#include "SETTINGS.h";
Texture::Texture() {

}
Texture::~Texture() {

}
void Texture::load(std::string filename) {
	ILuint imageId = ilGenImage();
	ilBindImage(imageId);
	wchar_t unicodeString[256]; 
	wsprintf(unicodeString, L"%S", filename.c_str());
	bool loaded = ilLoadImage(unicodeString);
	if (loaded) {
		if(IL_IMAGE_TYPE != IL_RGBA)
			ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		int width = ilGetInteger(IL_IMAGE_WIDTH);
		int height = ilGetInteger(IL_IMAGE_HEIGHT);
		int format = ilGetInteger(IL_IMAGE_FORMAT);
		int type = ilGetInteger(IL_IMAGE_TYPE);
		ILubyte * pixData = new ILubyte[IL_IMAGE_WIDTH * IL_IMAGE_HEIGHT];
		ilCopyPixels(0, 0, 0, width, height, 1, format, type, pixData);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixData);
		glGenerateMipmap(GL_TEXTURE_2D);
		ilDeleteImage(imageId);
	}
	else {
		msg::error::outErrMessage(filename, msg::error::errType::FILE_NOT_EXIST);
	}
}
void Texture::apply() {
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	switch (PROJECT_SETTINGS::TEXTURE::FILTER_VALUE) {
	case PROJECT_SETTINGS::TEXTURE::FILTER::ANISOTROPIC: {
		glTexParameterf(GL_TEXTURE_2D, PROJECT_SETTINGS::TEXTURE::FILTER_MODE, PROJECT_SETTINGS::TEXTURE::FILTER_ANISOTROPIC_VALUE);
	}; break;
	default: {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, PROJECT_SETTINGS::TEXTURE::FILTER_MIPMAP_MODE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, PROJECT_SETTINGS::TEXTURE::FILTER_MODE);
	};
	}
}
void Texture::disableAll() {
	glBindTexture(GL_TEXTURE_2D, 0);
}