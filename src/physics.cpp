#include "physics.hpp"
#include <BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h>
namespace CBlocks {
	Physics* Physics::sInstance;
	btRigidBody * Physics::create_capsule_rigid_body(float radius, float height) {
		auto rbc = btCapsuleShape(radius, height);
		auto motionState = btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), { 0,0,0 }));
		auto info = btRigidBody::btRigidBodyConstructionInfo(100.0f, &motionState, &rbc);
		auto rb = new btRigidBody(info);
		return rb;
	}
	Physics::Physics() {
		mBroadPhase = new btDbvtBroadphase();
		mCollisionConfiguration = new btDefaultCollisionConfiguration();
		mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);
		btGImpactCollisionAlgorithm::registerAlgorithm(mDispatcher);
		mSolver = new btSequentialImpulseConstraintSolver();
		mWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadPhase, mSolver, mCollisionConfiguration);
		mWorld->setGravity({ 0.0f,-9.8f, 0.0f });
		btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), { 0,0,0 }));
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