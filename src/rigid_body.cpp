#include "rigid_body.hpp"
#include <game_object.hpp>
namespace CBlocks {
	RigidBody::RigidBody(btRigidBody* rigidBody) : mRigidBody(rigidBody) {
		mType = ComponentType::Physics;
	}

	void RigidBody::update(double dt) {
		auto& tf = mRigidBody->getWorldTransform();
		auto& rot = tf.getRotation();
		Quaternion q(rot.x(), rot.y(), rot.z(), rot.w());
		owner->transform.set_rotation(q);
		auto& trans = tf.getOrigin();
		owner->transform.set_translation(trans.x(), trans.y(), trans.z());
	}
}