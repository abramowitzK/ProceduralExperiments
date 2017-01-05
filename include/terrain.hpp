#ifndef CBLOCKS_TERRAIN_HPP
#define CBLOCKS_TERRAIN_HPP
#include <FastNoise.h>
#include <vector>
#include <rendering.hpp>
#include <mesh.hpp>
namespace CBlocks {
	struct Terrain {
		Terrain(int width, int height, int sampling=1);
		void render(Renderer* renderer);

	private:
		Mesh mMesh;
		void generate_height_map();
		MeshData generate_mesh();
		FastNoise mNoise;
		int mWidth;
		int mHeight;
		int mSampling;
		std::vector<std::vector<float>> mHeightMap;

	};
}
#endif // !CBLOCKS_TERRAIN_HPP
