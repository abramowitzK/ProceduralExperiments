#pragma once
#include <component.hpp>
#include <mesh.hpp>
#include <render_state.hpp>
namespace Aurora {
struct Material;
struct MeshRenderer : public Component {
    MeshRenderer(Mesh* m, Material* mat) {
        material = mat;
        mesh     = m;
        mType    = ComponentType::Mesh;
    }
    Mesh*       mesh;
    RenderState required_state = DefaultRenderState;
    Material*   material;
};
} // namespace Aurora
