#pragma once
#include "events.hpp"
#include "vector_math.hpp"
namespace Aurora {
	struct Camera {
		Camera(EventManager& manager, int w, int h);
		void update(double dt);
		void render();
		Vector4 up, forward, position, rotation;
		Matrix4 view, projection;
		Vector4 velocity;
		float acceleration;
		float speed;
	private:
		Vector2 mPrevMouseTarget;
		Vector2 mMouseSpeed;
	};
}

