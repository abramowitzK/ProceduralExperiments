#pragma once
#include <map>
#include <vector_math.hpp>
#include <rendering.hpp>
namespace Aurora {
	struct World {
		int seed = 1337;
		int chunk_size = 16;
		bool do_lod = true;
		/*
		Resolution values for different chunks
		*/
		float LOD[4] = { 0.5f, 0.4f, 0.25f, 0.1f };
		void init(Vector3 cameraPos = {0,0,0});
		/*
		Figure out which levels of detail to load for each chunk
		*/
		void update(double dt, Vector3 cameraPos);
		void render(Renderer* renderer);
		float** mChunks;
	};
}