#include <mesh.hpp>
namespace Aurora {
	Mesh::Mesh(MeshData& data) {
		mNumIndices = (int)data.indices.size();
		init(data);
		mData = std::move(data);
	}

	Mesh & Mesh::operator=(Mesh && other) {
		mNumIndices = other.mNumIndices;
		mVao = other.mVao;
		mVbo = other.mVbo;
		mIbo = other.mIbo;
		mData = std::move(other.mData);
		return *this;
	}

	void Mesh::render() {
		glBindVertexArray(mVao);
		glDrawElements(GL_TRIANGLES, (GLsizei)mNumIndices, GL_UNSIGNED_INT, 0);
	}

	void Mesh::init(MeshData& data) {
		//TODO change to interleaved attributes
		glGenVertexArrays(1, &mVao);
		glBindVertexArray(mVao);
		glGenBuffers(1, &mVbo);
		glGenBuffers(1, &mIbo);
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3,GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)24);
		glBufferData(GL_ARRAY_BUFFER, data.vertices.size()*sizeof(Vertex), data.vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indices.size() * sizeof(int), data.indices.data(), GL_STATIC_DRAW);
	}

}