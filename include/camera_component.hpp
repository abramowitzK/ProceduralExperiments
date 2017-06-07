#pragma once
#include <vector_math.hpp>
#include <component.hpp>
#include <events.hpp>
namespace Aurora {
	struct Renderer;
	struct CameraComponent : public Component {
		CameraComponent(int w, int h, EventManager& manager);
		static void expose_to_script();
		void update(double dt);
		void render(Renderer* renderer);
		void rotate(float yaw, float pitch);
		Matrix4 view;
		Matrix4 proj;
		Vector4 up;
		Vector4 forward;
		Vector2 rotation;
	};
}