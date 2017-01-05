#ifndef CBLOCKS_MATERIAL_HPP
#define CBLOCKS_MATERIAL_HPP
#include <shader.hpp>
#include <render_state.hpp>
#include <vector_math.hpp>
#include <memory>
namespace CBlocks {
	struct Material {
		Material(){
			shader = new Shader("texturedLit.vert", "texturedLit.frag");
		}
		Shader* shader;
	};
	struct PBRMaterial : Material {

	};
}
#endif