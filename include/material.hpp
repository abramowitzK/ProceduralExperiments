#pragma once
#include <texture.hpp>
#include <vector>
namespace Aurora {
struct Shader;
struct Material {
    Material(Shader* shader, Texture t) : shader(shader) { tex.push_back(t); }
    Shader*              shader;
    std::vector<Texture> tex;
};
} // namespace Aurora
