#ifndef CBLOCKS_PHYSICS_HPP
#define CBLOCKS_PHYSICS_HPP
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <vector>
#include <rigid_body.hpp>
namespace CBlocks {
	enum class ColliderTypes {
		Box,
		Sphere,
		Capsule,
		Mesh,
	};
	struct Physics {
		
		~Physics();
		void fixed_update(double dt);
		btRigidBody* plane;
		static Physics* instance() {
			if (!sInstance)
				sInstance = new Physics();
			return sInstance;
		}
	private:
		Physics();
		static Physics* sInstance;
		std::vector<btRigidBody*> mRigidBodies;
		btBroadphaseInterface* mBroadPhase;
		btDefaultCollisionConfiguration* mCollisionConfiguration;
		btCollisionDispatcher* mDispatcher;
		btSequentialImpulseConstraintSolver* mSolver;
		btDiscreteDynamicsWorld* mWorld;
	};
}
#endif