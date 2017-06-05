#pragma once
#include <component.hpp>
#include <vector_math.hpp>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <script_manager.hpp>
#include <transform.hpp>
#include <camera_component.hpp>
namespace Aurora {
struct CharacterController : public Component {

	static void expose_to_script(ScriptManager* manager) {
		auto l = manager->get_lua_state();
		sol::usertype<CharacterController> type{
			"set_walk_dir", &CharacterController::set_walk_dir,
			"jump", &CharacterController::jump,
			"rotate", &CharacterController::rotate,
			"speed", sol::property(&CharacterController::speed)
		};
		l->set_usertype("CharacterController", type);
	}
	CharacterController(btKinematicCharacterController * controller) : mController(controller) {
		mGhost = controller->getGhostObject();
		mController->setJumpSpeed(200.0f);
		mController->setMaxJumpHeight(10.0f);
		mController->setMaxSlope(M_PI/4.0f);
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
		if (lastJump > 0.0) {
			lastJump-= dt; 
		}
	}
	void jump() {

		if (mController->canJump() && lastJump < 0.0) {
			printf("last jump %f \n", (float)lastJump);
			mController->jump({0,10,0});
			lastJump = cooldown;
		} else if(lastJump < 0.0){
			printf("Can't jump\n");
		}
	}
	void rotate(float yaw, float pitch) {
		auto mat = mGhost->getWorldTransform().getBasis();
		mat *= btMatrix3x3(btQuaternion(btVector3(0,1,0), yaw));
		auto strafe = mat[0];
		auto cam = mOwner->get_component<CameraComponent>(ComponentType::Camera);
		cam->mTransform->rotate_axis({strafe.x(), strafe.y(), strafe.z()}, pitch*100);
		mGhost->getWorldTransform().setBasis(mat);
	
	}
	//TODO handle other dirs and do rotation
	void set_walk_dir(bool forward, bool back, bool right, bool left, double dt) {
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
		if (back) {
			walkDirection -= forwardDir;
		}
		if (left) {
			walkDirection -= strafeDir;
		}
		if (right) {
			walkDirection += strafeDir;
		}
		mController->setVelocityForTimeInterval(walkDirection*speed, dt);
	}
	double lastJump = -1.0;
	double cooldown = 1.0;
	float speed = 10.0f;
	float walk_velocity = 0;
	Vector3 walkDir;
	btPairCachingGhostObject* mGhost;
	btKinematicCharacterController* mController;
};
}