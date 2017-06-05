#include "physics.hpp"
#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
#include <BulletCollision/CollisionShapes/btShapeHull.h>
#include <glm/gtc/type_ptr.hpp>
#include <gl/glew.h>

namespace Aurora {
	Physics* Physics::sInstance;
	void Physics::render(Renderer* renderer) {
		if(!debug)
			return;
		mWorld->debugDrawWorld();
		//auto cube = mRigidBodies[0];
		//btTransform t;
		//cube->getMotionState()->getWorldTransform(t);
		//mWorld->debugDrawObject(t, cube->getCollisionShape(), { 1.0,0.0,0.0 });

	}
	btKinematicCharacterController* Physics::create_character_controller(float radius, float height, Transform* t) {
		auto rbc = new  btCapsuleShape(1.0, 2.0);
		auto axis = rbc->getUpAxis();
		auto ghost = new btPairCachingGhostObject();
		btTransform trans;
		auto auroraTrans = t->get_transform();
		trans.setFromOpenGLMatrix(glm::value_ptr(t->get_transform()));
		ghost->setWorldTransform(trans);
		ghost->setCollisionShape(rbc);
		ghost->setCollisionFlags (btCollisionObject::CF_CHARACTER_OBJECT);
		auto kinematicController = new btKinematicCharacterController(ghost, rbc, 0.2f);
		kinematicController->setUseGhostSweepTest(false);
		kinematicController->setGravity({0,-9.8f,0});
		kinematicController->setUp(btVector3(0.0,1.0f,0.0));
		mWorld->addCollisionObject(ghost, btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);
		mWorld->addAction(kinematicController);
		auto basis = btMatrix3x3::getIdentity();
		ghost->getWorldTransform().setBasis(basis);
		return kinematicController;
	}
	btRigidBody * Physics::create_capsule_rigid_body(float radius, float height, Transform* t) {

		auto rbc = new  btBoxShape(btVector3(1.0f,1.0f,1.0f));
		/*auto quat = t->mRotation;
		auto trans = t->mTranslation;
		auto scale = t->mScale;
		btTransform transform = btTransform(btQuaternion(quat.x, quat.y, quat.z, quat.w), { trans.x, trans.y, trans.z });*/
		auto scale = t->mScale;
		btTransform transform;
		transform.setFromOpenGLMatrix(glm::value_ptr(t->get_transform()));
		auto rot = transform.getRotation();
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
		//auto quat = t->mRotation;
		//auto trans = t->mTranslation;
		auto scale = t->mScale;
		btTransform transform;
		transform.setIdentity();
		transform.setFromOpenGLMatrix(glm::value_ptr(t->get_transform()));
		auto motionState = new btDefaultMotionState(transform);
		btScalar mass = isStatic ? 0.0f : 1.0f;
		shape->setLocalScaling(btVector3(scale.x, scale.y, scale.z));
		auto info = btRigidBody::btRigidBodyConstructionInfo(mass, motionState, shape);
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
		mWorld->setGravity({ 0.0f,-4.8f, 0.0f });
		drawer = new GLDebugDrawer();
		drawer->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
		mWorld->setDebugDrawer(drawer);
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

	GLDebugDrawer::GLDebugDrawer() {
		glGenVertexArrays(1, &vao);

	}

	GLDebugDrawer::~GLDebugDrawer() {}

	void GLDebugDrawer::drawLine(const btVector3 & from, const btVector3 & to, const btVector3 & fromColor, const btVector3 & toColor) {
			float tmp[6] ={ from.getX(), from.getY(), from.getZ(),
				to.getX(), to.getY(), to.getZ() };

			glPushMatrix();
			{
				glColor4f(fromColor.getX(), fromColor.getY(), fromColor.getZ(), 1.0f);
				glVertexPointer(3,
								GL_FLOAT,
								0,
								&tmp);

				glPointSize(5.0f);
				glDrawArrays(GL_POINTS, 0, 2);
				glDrawArrays(GL_LINES, 0, 2);
			}
			glPopMatrix();
	}

	void GLDebugDrawer::drawLine(const btVector3 & from, const btVector3 & to, const btVector3 & color) {
		glBindVertexArray(vao);
		float tmp[6] ={ from.getX(), from.getY(), from.getZ(),
			to.getX(), to.getY(), to.getZ() };
		glLineWidth(5.0f);
		auto err = glGetError();
		glBegin(GL_LINES);
//		glColor4f(1.0f, 0.0f,0.0f,1.0f);

		glVertex3f(from.x(), from.y(), from.z());
		glVertex3f(to.x(), to.y(), to.z());
		glEnd();
		err = glGetError();
	}

	void GLDebugDrawer::drawSphere(const btVector3 & p, btScalar radius, const btVector3 & color) {}

	void GLDebugDrawer::drawTriangle(const btVector3 & a, const btVector3 & b, const btVector3 & c, const btVector3 & color, btScalar alpha) {}

	void GLDebugDrawer::drawContactPoint(const btVector3 & PointOnB, const btVector3 & normalOnB, btScalar distance, int lifeTime, const btVector3 & color) {}

	void GLDebugDrawer::reportErrorWarning(const char * warningString) {
		printf("Error in debug drawing!");
	}

	void GLDebugDrawer::draw3dText(const btVector3 & location, const char * textString) {}

	void GLDebugDrawer::setDebugMode(int debugMode) {
		m_debugMode = debugMode;
	}

}