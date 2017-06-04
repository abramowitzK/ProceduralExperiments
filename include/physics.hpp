#pragma once
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <vector>
#include <rigid_body.hpp>
#include <vector_math.hpp>
#include <transform.hpp>
namespace Aurora {
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
		btKinematicCharacterController* create_character_controller(float radius, float height, Transform* t);
		btRigidBody* create_capsule_rigid_body(float radius, float height, Transform* t);
		btRigidBody* create_box_rigid_body(bool isStatic, Vector3 min, Vector3 max, Transform* t);
		btRigidBody* create_convex_hull_rigid_body(bool isStatic, Mesh* mesh, Transform* t);
	private:
		Physics();
		btBvhTriangleMeshShape* create_bvh_triangle_mesh_shape(Mesh* mesh);
		btConvexHullShape* create_convex_hull_shape(Mesh* mesh);
		static Physics* sInstance;
		std::vector<btRigidBody*> mRigidBodies;
		btBroadphaseInterface* mBroadPhase;
		btDefaultCollisionConfiguration* mCollisionConfiguration;
		btCollisionDispatcher* mDispatcher;
		btSequentialImpulseConstraintSolver* mSolver;
		btDiscreteDynamicsWorld* mWorld;
	};
}