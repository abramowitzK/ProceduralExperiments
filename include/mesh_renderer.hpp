#pragma once
#include <component.hpp>
#include <mesh.hpp>
namespace Aurora {
	struct MeshRenderer : public Component{
		MeshRenderer(Mesh* m, Material* mat){
			material = mat;
			mesh = m;
			mType = ComponentType::Mesh;
		}
		Mesh* mesh;
		RenderState required_state = DefaultRenderState;
		Material* material;
	};
}
