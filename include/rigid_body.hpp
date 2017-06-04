#pragma once
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <component.hpp>
namespace Aurora {

	struct RigidBody : public Component {
		RigidBody(btRigidBody* rigidBody, bool isStatic = false);
		void update(double dt);
		btRigidBody* mRigidBody;
		bool mIsStatic = false;
	};
}