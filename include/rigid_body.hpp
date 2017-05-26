#pragma once
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <component.hpp>
namespace Aurora {

	struct RigidBody : public Component {
		RigidBody(btRigidBody* rigidBody);
		void update(double dt);
		btRigidBody* mRigidBody;
	};
}