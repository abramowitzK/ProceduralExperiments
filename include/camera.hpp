/*
* Created by Kyle on 12/11/2016.
* Copyright (c) 2016 Kyle All rights reserved.
*/

#ifndef CBLOCKS_CAMERA_HPP
#define CBLOCKS_CAMERA_HPP
#include "events.hpp"
#include "vector_math.hpp"
#include <component.hpp>
namespace CBlocks {
	struct Camera : public Component {
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
#endif //CBLOCKS_CAMERA_HPP
