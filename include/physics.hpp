#ifndef CBLOCKS_PHYSICS_HPP
#define CBLOCKS_PHYSICS_HPP
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <vector>
#include <rigid_body.hpp>
#include <vector_math.hpp>
#include <transform.hpp>
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
		btRigidBody* create_capsule_rigid_body(float radius, float height);
		btRigidBody* create_box_rigid_body(bool isStatic, Vector3 min, Vector3 max, Transform t);
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
#endif