#include "physics.hpp"
#include <BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h>
namespace CBlocks {
	Physics* Physics::sInstance;
	Physics::Physics() {
		mBroadPhase = new btDbvtBroadphase();
		mCollisionConfiguration = new btDefaultCollisionConfiguration();
		mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);
		btGImpactCollisionAlgorithm::registerAlgorithm(mDispatcher);
		mSolver = new btSequentialImpulseConstraintSolver();
		mWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadPhase, mSolver, mCollisionConfiguration);
		mWorld->setGravity({ 0.0f,-9.8f, 1.0f });
		btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), { 0,-1,0 }));
		btCollisionShape* groundShape = new btSphereShape(10.0);
		btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, {0,0,0});
		btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
		btVector3 inertia; groundShape->calculateLocalInertia(10.0, inertia);
		groundRigidBody->setMassProps(1.0, inertia);
		mWorld->addRigidBody(groundRigidBody);
		plane = groundRigidBody;
	}

	Physics::~Physics() {}

	void Physics::fixed_update(double dt) {
		mWorld->stepSimulation(dt, 1, dt);
	}

}