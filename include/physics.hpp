#ifndef CBLOCKS_PHYSICS_HPP
#define CBLOCKS_PHYSICS_HPP
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
namespace CBlocks {

	struct Physics {
		Physics();
		~Physics();
		void fixed_update(double dt);
	private:
		btBroadphaseInterface* mBroadPhase;
		btDefaultCollisionConfiguration* mCollisionConfiguration;
		btCollisionDispatcher* mDispatcher;
		btSequentialImpulseConstraintSolver* mSolver;
		btDiscreteDynamicsWorld* mWorld;
	};
}
#endif