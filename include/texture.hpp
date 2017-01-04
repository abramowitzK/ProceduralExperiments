#ifndef CBLOCKS_TEXTURE_H
#define CBLOCKS_TEXTURE_H
#include <GL\glew.h>
#include <string>
namespace CBlocks {
	struct Texture {
		GLuint Tex;
		int width;
		int height;
		int comp;
	};

	Texture create_2d_texture(std::string &filepath);
}
#endif
