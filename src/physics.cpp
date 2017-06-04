#include "physics.hpp"
#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
#include <BulletCollision/CollisionShapes/btShapeHull.h>

#include <glm/gtc/type_ptr.hpp>

namespace Aurora {
	Physics* Physics::sInstance;
	btKinematicCharacterController* Physics::create_character_controller(float radius, float height, Transform* t) {
		auto rbc = new  btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
		auto ghost = new btPairCachingGhostObject();
		btTransform trans;
		trans.setFromOpenGLMatrix(glm::value_ptr(t->get_transform()));
		ghost->setWorldTransform(trans);
		ghost->setCollisionShape(rbc);
		ghost->setCollisionFlags (btCollisionObject::CF_CHARACTER_OBJECT);
		auto kinematicController = new btKinematicCharacterController(ghost, rbc, 1.0f);
		return kinematicController;
		mWorld->addCollisionObject(ghost, btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);
		mWorld->addAction(kinematicController);
	}
	btRigidBody * Physics::create_capsule_rigid_body(float radius, float height, Transform* t) {

		auto rbc = new  btBoxShape(btVector3(1.0f,1.0f,1.0f));
		btTransform transform;
		transform.setIdentity();
		auto scale = t->mScale;
		transform.setFromOpenGLMatrix(glm::value_ptr(t->get_transform()));
		auto motionState = new btDefaultMotionState(transform);
		btVector3 inertia;
		rbc->calculateLocalInertia(100.0f, inertia);
		rbc->setLocalScaling(btVector3(scale.x, scale.y, scale.z));
		auto info = btRigidBody::btRigidBodyConstructionInfo(100.0f, motionState, rbc, inertia);
		info.m_restitution = 0.4f;
		info.m_friction = 0.3f;
		auto body = new btRigidBody(info);
		body->setLinearFactor(btVector3(1, 1, 0));
		mWorld->addRigidBody(body);
		mRigidBodies.push_back(body);
		return body;
	}
	btRigidBody * Physics::create_box_rigid_body(bool isStatic, Vector3 min, Vector3 max, Transform* t) {
		auto extents = min-max;
		auto rb = new btBoxShape({extents.x, extents.y, extents.z});
		btTransform transform;
		transform.setIdentity();
		transform.setFromOpenGLMatrix(glm::value_ptr(t->get_transform()));
		auto motionState = new btDefaultMotionState(transform);
		auto mass = isStatic ? 0.0f : 100.0f;
		auto info = btRigidBody::btRigidBodyConstructionInfo(mass, motionState, rb);
		auto body = new btRigidBody(info);
		return body;
	}
	btRigidBody * Physics::create_convex_hull_rigid_body(bool isStatic, Mesh * mesh, Transform* t) {
		auto shape = create_bvh_triangle_mesh_shape(mesh);
		//shape->initializePolyhedralFeatures();
		//shape->optimizeConvexHull();
		auto quat = t->mRotation;
		auto trans = t->mTranslation;
		auto scale = t->mScale;
		/*btTransform transform;
		transform.setIdentity();
		transform.setFromOpenGLMatrix(glm::value_ptr(t->get_transform()));*/
		auto motionState = new btDefaultMotionState(btTransform(btQuaternion(quat.x, quat.y, quat.z, quat.w), { trans.x, trans.y, trans.z }));
		btScalar mass = isStatic ? 0.0f : 1.0f;

		btVector3 inertia(0,0,0);
		shape->setLocalScaling(btVector3(scale.x, scale.y, scale.z));
		auto info = btRigidBody::btRigidBodyConstructionInfo(mass, motionState, shape, inertia);
		info.m_restitution = 1.0f;
		info.m_friction = 0.5f;
		auto body = new btRigidBody(info);
		body->setLinearFactor(btVector3(1,1,0));
		mWorld->addRigidBody(body);
		mRigidBodies.push_back(body);
		return body;
	}
	Physics::Physics() {
		mBroadPhase = new btDbvtBroadphase();
		mCollisionConfiguration = new btDefaultCollisionConfiguration();
		mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);
		btGImpactCollisionAlgorithm::registerAlgorithm(mDispatcher);
		mSolver = new btSequentialImpulseConstraintSolver();
		mWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadPhase, mSolver, mCollisionConfiguration);
		mWorld->setGravity({ 0.0f,-9.8f, 0.0f });
	}

	btBvhTriangleMeshShape * Physics::create_bvh_triangle_mesh_shape(Mesh * mesh) {
		auto data = mesh->get_data();
		const auto& vertices = data->vertices;
		auto bullet_mesh = new btTriangleMesh();
		for (int i = 0; i < data->get_num_indices(); i +=3) {
			btVector3 v1,v2,v3;
			v1 = btVector3(vertices[data->indices[i]].pos.x, vertices[data->indices[i]].pos.y, vertices[data->indices[i]].pos.z);
			v2 = btVector3(vertices[data->indices[i+1]].pos.x, vertices[data->indices[i+1]].pos.y, vertices[data->indices[i+1]].pos.z);
			v3 = btVector3(vertices[data->indices[i+2]].pos.x, vertices[data->indices[i+2]].pos.y, vertices[data->indices[i+2]].pos.z);
			bullet_mesh->addTriangle(v1, v2, v3);
		}
		//auto verts = new btScalar[data->get_num_vertices()*3];
		//for (int i = 0; i < data->get_num_vertices(); i++) {
		//	verts[i * 3] = vertices[i].pos.x;
		//	verts[i * 3 + 1] = vertices[i].pos.y;
		//	verts[i * 3 + 2] = vertices[i].pos.z;
		//}

		//auto indices = new int[data->get_num_indices()];
		//memcpy(indices, data->indices.data(), data->get_num_indices() * sizeof(int));
		//auto iva = new btTriangleIndexVertexArray(data->get_num_indices() / 3, indices,  sizeof(int), data->get_num_vertices(), verts, sizeof(btScalar) * 3);
		auto shape = new btBvhTriangleMeshShape(bullet_mesh, true);
		return shape;
	}


	btConvexHullShape * Physics::create_convex_hull_shape(Mesh * mesh) {
		auto data = mesh->get_data();
		const auto& vertices = data->vertices;
		auto verts = new btScalar[data->get_num_vertices()*3];
		for (int i = 0; i < data->get_num_vertices(); i++) {
			verts[i * 3] = vertices[i].pos.x;
			verts[i * 3 + 1] = vertices[i].pos.y;
			verts[i * 3 + 2] = vertices[i].pos.z;
		}
		//According to the docs, this makes a copy of the points so it should be safe to delete here.
		auto test = sizeof(btVector3);
		auto shape = new btConvexHullShape(verts, data->get_num_vertices(), 12);
		return shape;
		//auto hull = new btShapeHull(shape);
		//hull->buildHull(shape->getMargin());
		//return new btConvexHullShape((btScalar*)hull->getVertexPointer(), hull->numVertices(), 12);
	}

	Physics::~Physics() {}

	void Physics::fixed_update(double dt) {
		mWorld->stepSimulation(dt, 2);
	}

}