#pragma once
#include "texture.hpp"
#include "vector_math.hpp"
#include "structures.hpp"
namespace Aurora {
	struct Sprite {
		Texture *Tex;
		Vector2 Pos;
		Vector2 Dim;
		Color Col;
		float depth;
	};
}
