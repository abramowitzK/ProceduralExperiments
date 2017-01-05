#ifndef CBLOCKS_MESH_HPP
#define CBLOCKS_MESH_HPP
#include <vector>
#include <vector_math.hpp>
#include <GL\glew.h>
namespace CBlocks {
	struct Vertex {
		Vector3 pos;
		Vector3 normal;
		Vector2 texCoords;
	};
	struct MeshData {
		int numIndices;
		int numVerts;
		int* indices;
		Vector3* vertices;
		Vector3* normals;
		Vector2* uvs;
	};
	struct Mesh {
		Mesh() {};
		Mesh(MeshData data);
		void render();
	private:
		void init();
		GLuint mVbo;
		GLuint mIbo;
		GLuint mVao;
		MeshData mMesh;
	};
}
#endif