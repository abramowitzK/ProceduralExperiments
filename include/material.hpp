#pragma once
#include <shader.hpp>
#include <render_state.hpp>
#include <vector_math.hpp>
#include <memory>
#include <texture.hpp>
namespace Aurora {
	struct Material {
		Material(Shader* shader, Texture t) : shader(shader), tex(t){
		}
		Shader* shader;
		Texture tex;
	};
}