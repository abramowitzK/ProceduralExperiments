#pragma once
#include <vector>
#include <rigid_body.hpp>
#include <vector_math.hpp>
#include <transform.hpp>
#include <rendering.hpp>
namespace Aurora {
	enum class ColliderTypes {
		Box,
		Sphere,
		Capsule,
		Mesh,
	};
	struct Physics {
		
		~Physics();
		void fixed_update(double dt);
		static Physics* instance() {
			if (!sInstance)
				sInstance = new Physics();
			return sInstance;
		}
		bool debug = true;
		void render(Renderer* renderer);
	private:
		Physics();
		static Physics* sInstance;
	};
}