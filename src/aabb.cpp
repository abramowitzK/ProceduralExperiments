#include <aabb.hpp>
namespace CBlocks {
	AABB::AABB(Vector3 min, Vector3 max) : Min(min), Max(max){}

	Vector3 AABB::get_size() {
		return (Max - Min);
	}

	Vector3 AABB::get_half_size() {
		return (Max - Min) *0.5f;
	}
	Vector3 AABB::get_center() {
		return (Max + Min)*0.5f;
	}
}