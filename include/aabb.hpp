#ifndef CBLOCKS_AABB_HPP
#define CBLOCKS_AABB_HPP
#include <vector_math.hpp>
namespace CBlocks {
	struct AABB {
		AABB(Vector3 min, Vector3 Max);
		Vector3 get_size();
		Vector3 get_half_size();
		Vector3 get_center();
		Vector3 Min;
		Vector3 Max;
	};
}
#endif