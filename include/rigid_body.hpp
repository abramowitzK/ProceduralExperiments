#pragma once
#include <component.hpp>
namespace Aurora {

	struct RigidBody : public Component {
		RigidBody(bool isStatic = false);
		void update(double dt);
		bool mIsStatic = false;
	};
}