#include "physics.hpp"

namespace Aurora {
	Physics* Physics::sInstance;
	void Physics::render(Renderer* renderer) {
		if (!debug)
			return;
	}

	Physics::Physics() {
	}

	Physics::~Physics() {}

	void Physics::fixed_update(double dt) {
	}

}