#pragma once
#include <GL\glew.h>
#include <vector>
#include <vector_math.hpp>
namespace Aurora {
struct Vertex {
    Vector3 pos;
    Vector3 normal;
    Vector2 texCoords;
};
struct MeshData {
    MeshData() {}
    std::vector<Vertex>   vertices;
    std::vector<unsigned> indices;
    MeshData(MeshData&& o) noexcept : vertices(std::move(o.vertices)), indices(std::move(o.indices)) {}
    MeshData& operator=(MeshData&& other) {
        vertices = std::move(other.vertices);
        indices  = std::move(other.indices);
        return *this;
    }
    int get_num_vertices() { return (int)vertices.size(); }
    int get_num_indices() { return (int)indices.size(); }
};
struct Mesh {
    Mesh() {}
    Mesh(MeshData& data);
    Mesh(Mesh&& o) noexcept
        : mVbo(o.mVbo), mIbo(o.mIbo), mVao(o.mVao), mNumIndices(o.mNumIndices), mData(std::move(o.mData)) {}
    // Don't want to be copying these things around. Way too expensive.
    Mesh(const Mesh& o) = delete;
    Mesh&     operator=(Mesh other) = delete;
    Mesh&     operator              =(Mesh&& other);
    void      render();
    MeshData* get_data() { return &mData; }

  private:
    void     init(MeshData& data);
    GLuint   mVbo;
    GLuint   mIbo;
    GLuint   mVao;
    int      mNumIndices;
    MeshData mData;
};
} // namespace Aurora
