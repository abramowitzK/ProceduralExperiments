#ifndef CBLOCKS_SPRITE_H
#define CBLOCKS_SPRITE_H
#include "texture.hpp"
#include "vector_math.hpp"
#include "structures.hpp"
namespace CBlocks {
	struct Sprite {
		Texture *Tex;
		Vector2 Pos;
		Vector2 Dim;
		Color Col;
		float depth;
	};
}
#endif
