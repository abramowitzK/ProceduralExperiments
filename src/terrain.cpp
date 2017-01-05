#include "terrain.hpp"

namespace CBlocks {
	Terrain::Terrain(int width, int height, int sampling) : mWidth(width), mHeight(height), mSampling(sampling) {
		mHeightMap.resize(width);
		mHeightMap.resize(height);
		mNoise.SetNoiseType(FastNoise::NoiseType::Simplex);
	}

	void Terrain::render(Renderer * renderer) {}

	void Terrain::generate_height_map() {
		for (int i = 0; i < mWidth; i++) {
			for (int j = 0; j < mHeight; j++) {
				mHeightMap[i][j] = mNoise.GetNoise((float)i, (float)j);
			}
		}
	}

	MeshData Terrain::generate_mesh() {
		MeshData data;
		//data.numVerts = mHeight*mWidth*(mSampling-1);
		//data.vertices = new Vector3[data.numVerts];
		//for (int i = 0; i < mWidth*mSampling; i++) {
		//	for (int j = 0; j < mHeight; j++) {
		//		data.vertices[i + j] = { i,0,j };
		//	}
		//}
		return data;
	}

}