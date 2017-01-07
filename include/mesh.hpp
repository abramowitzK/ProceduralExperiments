#ifndef CBLOCKS_MESH_HPP
#define CBLOCKS_MESH_HPP
#include <vector>
#include <vector_math.hpp>
#include <GL\glew.h>
#include <component.hpp>
#include <render_state.hpp>
#include <material.hpp>
namespace CBlocks {
	struct Vertex {
		Vector3 pos;
		Vector3 normal;
		Vector2 texCoords;
	};
	struct MeshData {
		std::vector<Vertex> vertices;
		std::vector<unsigned> indices;
	};
	struct Mesh {
		Mesh() {}
		Mesh(MeshData& data);
		void render();
	private:
		void init(MeshData& data);
		GLuint mVbo;
		GLuint mIbo;
		GLuint mVao;
		int mNumIndices;
	};
}
#endif