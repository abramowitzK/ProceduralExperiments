#ifndef CBLOCKS_MATERIAL_HPP
#define CBLOCKS_MATERIAL_HPP
#include <shader.hpp>
#include <render_state.hpp>
#include <vector_math.hpp>
#include <memory>
namespace CBlocks {
	struct Material {
		Material(){
			shader = std::make_shared<Shader>("texturedLit.vert", "texturedLit.frag");
		}
		std::shared_ptr<Shader> shader;
	};
	struct PBRMaterial : Material {

	};
}
#endif