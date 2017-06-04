#include "rigid_body.hpp"
#include <game_object.hpp>
namespace Aurora {
	RigidBody::RigidBody(btRigidBody* rigidBody, bool isStatic) : mRigidBody(rigidBody), mIsStatic(isStatic) {
		mType = ComponentType::Physics;
	}

	void RigidBody::update(double dt) {
		if(!mIsStatic) {
			btTransform tf;
			mRigidBody->getMotionState()->getWorldTransform(tf);
			auto& rot = tf.getRotation();
			Quaternion q = Quaternion(rot.getW(), rot.getX(), rot.getY(), rot.getZ());

			auto vec = glm::eulerAngles(q);
			mOwner->transform.set_rotation(q);
			auto& trans = tf.getOrigin();
			mOwner->transform.set_translation(trans.x(), trans.y(), trans.z());
		}
	}
}