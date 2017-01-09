#ifndef CBLOCKS_RIGID_BODY_HPP
#define CBLOCKS_RIGID_BODY_HPP
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <component.hpp>
namespace CBlocks {

	struct RigidBody : public Component {
		RigidBody();
		void fixed_update(double dt);
		btRigidBody* mRigidBody;
	};
}

#endif