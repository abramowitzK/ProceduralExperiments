#include <Chunk.h>
#include <GL\glew.h>
#include <iostream>
namespace CBlocks {
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	Chunk::Chunk() {
		// Create the blocks
		m_blocks = new Block**[CHUNK_SIZE];
		for (int i = 0; i < CHUNK_SIZE; i++) {
			m_blocks[i] = new Block*[CHUNK_SIZE];
			for (int j = 0; j < CHUNK_SIZE; j++) {
				m_blocks[i][j] = new Block[CHUNK_SIZE];
			}
		}
		//Generate a vao to encapsulate all the buffer state for this object
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);
		//Generate a vbo and ibo
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ibo);
		//Bind the vbo to buffer data
		vector<Vector3> verts;
		vector<unsigned> indices;
		Generate(verts, indices);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vector3), verts.data(), GL_STATIC_DRAW);
		auto err = glGetError();
		glEnableVertexAttribArray(0); //Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), GL_STATIC_DRAW);
		err = glGetError();
	}


	Chunk::~Chunk() {
		// Delete the blocks
		for (int i = 0; i < CHUNK_SIZE; ++i) {
			for (int j = 0; j < CHUNK_SIZE; ++j) {
				delete[] m_blocks[i][j];
			}

			delete[] m_blocks[i];
		}
		delete[] m_blocks;
	}

	void Chunk::Render() {
		glBindVertexArray(m_vao);
		glDrawElements(GL_TRIANGLES, CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE * 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void Chunk::Generate(vector<Vector3>& verts, vector<unsigned>& indices) {
		//This is super slow but it's a base to start off with
		//We shouldn't need this much data. This is like 67 mb with 128x128x128 chunks
		verts.reserve(CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE * 8);
		indices.reserve(CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE * 36);
		for (int i = 0; i < CHUNK_SIZE; i++) {
			for (int j = 0; j < CHUNK_SIZE; j++) {
				for (int k = 0; k < CHUNK_SIZE; k++) {
					CreateCube(i, j, k, verts);
				}
			}
		}
		for (int i = 0; i < verts.size(); i += 8) {
			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back(i + 2);

			indices.push_back(i);
			indices.push_back(i + 2);
			indices.push_back(i + 3);

			indices.push_back(i + 4);
			indices.push_back(i + 5);
			indices.push_back(i + 6);

			indices.push_back(i + 4);
			indices.push_back(i + 6);
			indices.push_back(i + 7);

			indices.push_back(i + 1);
			indices.push_back(i + 4);
			indices.push_back(i + 7);

			indices.push_back(i + 1);
			indices.push_back(i + 7);
			indices.push_back(i + 2);

			indices.push_back(i + 5);
			indices.push_back(i);
			indices.push_back(i + 3);

			indices.push_back(i + 5);
			indices.push_back(i + 3);
			indices.push_back(i + 6);

			indices.push_back(i + 3);
			indices.push_back(i + 2);
			indices.push_back(i + 7);

			indices.push_back(i + 3);
			indices.push_back(i + 7);
			indices.push_back(i + 6);

			indices.push_back(i + 5);
			indices.push_back(i + 4);
			indices.push_back(i + 1);

			indices.push_back(i + 5);
			indices.push_back(i + 1);
			indices.push_back(i);
		}
	}

	void Chunk::CreateCube(int x, int y, int z, vector<Vector3>& verts) {
		Vector3 p1(x - Block::BLOCK_RENDER_SIZE, y - Block::BLOCK_RENDER_SIZE, z + Block::BLOCK_RENDER_SIZE);
		Vector3 p2(x + Block::BLOCK_RENDER_SIZE, y - Block::BLOCK_RENDER_SIZE, z + Block::BLOCK_RENDER_SIZE);
		Vector3 p3(x + Block::BLOCK_RENDER_SIZE, y + Block::BLOCK_RENDER_SIZE, z + Block::BLOCK_RENDER_SIZE);
		Vector3 p4(x - Block::BLOCK_RENDER_SIZE, y + Block::BLOCK_RENDER_SIZE, z + Block::BLOCK_RENDER_SIZE);
		Vector3 p5(x + Block::BLOCK_RENDER_SIZE, y - Block::BLOCK_RENDER_SIZE, z - Block::BLOCK_RENDER_SIZE);
		Vector3 p6(x - Block::BLOCK_RENDER_SIZE, y - Block::BLOCK_RENDER_SIZE, z - Block::BLOCK_RENDER_SIZE);
		Vector3 p7(x - Block::BLOCK_RENDER_SIZE, y + Block::BLOCK_RENDER_SIZE, z - Block::BLOCK_RENDER_SIZE);
		Vector3 p8(x + Block::BLOCK_RENDER_SIZE, y + Block::BLOCK_RENDER_SIZE, z - Block::BLOCK_RENDER_SIZE);
		verts.push_back(p1);
		verts.push_back(p2);
		verts.push_back(p3);
		verts.push_back(p4);
		verts.push_back(p5);
		verts.push_back(p6);
		verts.push_back(p7);
		verts.push_back(p8);
	}
}
