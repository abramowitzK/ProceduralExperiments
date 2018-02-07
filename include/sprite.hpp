#pragma once
#include "structures.hpp"
#include "texture.hpp"
#include "vector_math.hpp"
namespace Aurora {
struct Sprite {
    Texture* Tex;
    Vector2  Pos;
    Vector2  Dim;
    Color    Col;
    float    depth;
};
} // namespace Aurora
