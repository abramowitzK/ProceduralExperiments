#ifndef CBLOCKS_MESH_RENDERER_HPP
#define CBLOCKS_MESH_RENDERER_HPP
#include <component.hpp>
#include <mesh.hpp>
namespace CBlocks {
	struct MeshRenderer : public Component{
		MeshRenderer(Mesh* m, Material* mat) : mesh(m), material(mat){
			mType = ComponentType::Mesh;
		}
		Mesh* mesh;
		RenderState required_state = DefaultRenderState;
		Material* material;
	};
}
#endif // !CBLOCKS_MESH_RENDERER_HPP
