#ifndef CBLOCKS_CHUNK_H
#define CBLOCKS_CHUNK_H
#include <GL\glew.h>
#include "block.h"
#include <vector>
#include "vector_math.hpp"
using namespace std;
namespace CBlocks {
	class Chunk {
	public:
		static const int CHUNK_SIZE = 1;

		Chunk();

		~Chunk();

		void Render();

	private:
		void Generate(vector<Vector3> &verts, vector<unsigned> &indices);

		void CreateCube(int x, int y, int z, vector<Vector3> &verts);

	private:
		Block ***m_blocks;
		GLuint m_vao;
		GLuint m_vbo;
		GLuint m_ibo;
		int count;
	};
}
#endif
