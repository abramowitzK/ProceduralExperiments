#pragma once
#include <component.hpp>
#include <vector_math.hpp>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
namespace Aurora {
struct CharacterController : public Component {
	CharacterController(btKinematicCharacterController * controller) : mController(controller) {
		mGhost = controller->getGhostObject();
		mType = ComponentType::CharacterController;
	}
	void CharacterController::update(double dt) {
		btTransform tf = mGhost->getWorldTransform();
		auto& rot = tf.getRotation();
		Quaternion q = Quaternion(rot.getW(), rot.getX(), rot.getY(), rot.getZ());
		auto vec = glm::eulerAngles(q);
		mOwner->transform.set_rotation(q);
		auto& trans = tf.getOrigin();
		mOwner->transform.set_translation(trans.x(), trans.y(), trans.z());
		auto walkVelocity = speed;
		auto walkSpeed = walkVelocity * (float)dt;
	}
	void jump() {
		if (mController->canJump()) {
			mController->jump();
		}
	}
	//TODO handle other dirs and do rotation
	void set_walk_dir(bool forward) {
		btTransform xform;
		xform = mGhost->getWorldTransform ();
		btVector3 forwardDir = xform.getBasis()[2];
		btVector3 upDir = xform.getBasis()[1];
		btVector3 strafeDir = xform.getBasis()[0];
		forwardDir.normalize ();
		upDir.normalize ();
		strafeDir.normalize ();
		auto walkDirection = btVector3(0, 0, 0);
		//Forward
		if (forward) {
			walkDirection += forwardDir;
		}
	}
	float speed = 10.0f;
	float walk_velocity = 0;
	Vector3 walkDir;
	btPairCachingGhostObject* mGhost;
	btKinematicCharacterController* mController;
};
}