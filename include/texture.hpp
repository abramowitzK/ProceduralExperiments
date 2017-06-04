#pragma once
#include <GL/glew.h>
#include <string>
namespace Aurora {
	struct Texture {
		GLuint Tex;
		int width;
		int height;
		int comp;
		std::string name;
	};

	Texture create_2d_texture(std::string &filepath);
}