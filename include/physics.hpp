#pragma once
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <LinearMath/btIDebugDraw.h>
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
		bool debug = true;
		void render(Renderer* renderer);
		btIDebugDraw* drawer;
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
	class GLDebugDrawer : public btIDebugDraw {

		int m_debugMode;

	public:

		GLDebugDrawer();
		virtual ~GLDebugDrawer();

		virtual void   drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor);

		virtual void   drawLine(const btVector3& from, const btVector3& to, const btVector3& color);

		virtual void   drawSphere(const btVector3& p, btScalar radius, const btVector3& color);

		virtual void   drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha);

		virtual void   drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);

		virtual void   reportErrorWarning(const char* warningString);

		virtual void   draw3dText(const btVector3& location, const char* textString);

		virtual void   setDebugMode(int debugMode);
		virtual int      getDebugMode() const { return m_debugMode; }
		GLuint vao;
	};
}