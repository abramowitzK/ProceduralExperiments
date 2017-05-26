#include <GL/glew.h>
#include "texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
namespace Aurora {
	Texture create_2d_texture(std::string &filepath) {
		stbi_set_flip_vertically_on_load(true);
		Texture t;
		glGenTextures(1, &t.Tex);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, t.Tex);
		auto image = stbi_load(filepath.c_str(), &t.width, &t.height, &t.comp, 0);
		if(t.comp == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t.width, t.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		} else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t.width, t.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(image);
		glBindTexture(GL_TEXTURE_2D, 0);
		return t;
	}
}
