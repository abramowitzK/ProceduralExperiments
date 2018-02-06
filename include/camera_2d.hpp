#pragma once
#include <vector_math.hpp>
#include <component.hpp>
#include <events.hpp>
namespace Aurora {
	struct Camera2D : public Component {
		Camera2D(EventManager& manager, int w, int h);
		void update(double dt);
		void render();
		const Vector4 up = { 0,1,0,1 }; 
		Vector4 forward, position, rotation;
		Matrix4 view, projection;
		Vector4 velocity;
		float acceleration;
		float speed;
	private:
		Vector2 mPrevMouseTarget;
		Vector2 mMouseSpeed;
	};
}