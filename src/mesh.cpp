#include "mesh.hpp"
namespace CBlocks {
	Mesh::Mesh(MeshData data) {
		mMesh = data;
		init();
	}

	void Mesh::render() {
		glBindVertexArray(mVao);
		glDrawElements(GL_TRIANGLES, mMesh.numIndices, GL_INT, 0);
	}

	void Mesh::init() {
		//TODO change to interleaved attributes
		glGenVertexArrays(1, &mVao);
		glBindVertexArray(mVao);
		glGenBuffers(1, &mVbo);
		glGenBuffers(1, &mIbo);
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3,GL_FLOAT, GL_FALSE, 0, (void*)(mMesh.numVerts*sizeof(Vector3)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(mMesh.numVerts * sizeof(Vector3) * 2));
		glBufferData(GL_ARRAY_BUFFER, mMesh.numVerts*8*sizeof(float), mMesh.vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mMesh.numIndices * sizeof(int), mMesh.indices, GL_STATIC_DRAW);
	}

}