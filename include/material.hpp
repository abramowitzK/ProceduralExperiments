#ifndef CBLOCKS_MATERIAL_HPP
#define CBLOCKS_MATERIAL_HPP
#include <shader.hpp>
#include <render_state.hpp>
#include <vector_math.hpp>
namespace CBlocks {
	struct Material {
		shared_ptr<Shader> shader;
	};
	struct PBRMaterial : Material {

	};
}
#endif