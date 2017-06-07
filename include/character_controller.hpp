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
		mController->setMaxPenetrationDepth(0.01);
		mType = ComponentType::CharacterController;
	}
	void CharacterController::update(double dt) {

		auto mat = mGhost->getWorldTransform().getBasis();
		mat *= btMatrix3x3(btQuaternion(btVector3(0, 0, 1), 0))*btMatrix3x3(btQuaternion(btVector3(1, 0, 0), 0));
		mGhost->getWorldTransform().setBasis(mat);
		btTransform tf = mGhost->getWorldTransform();
		auto& rot = tf.getRotation();
		Quaternion q = Quaternion(rot.getW(), rot.getX(), rot.getY(), rot.getZ());
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
		auto cam = mOwner->get_component<CameraComponent>(ComponentType::Camera);
		//cam->mTransform->mRotation =  q*cam->mTransform->mRotation;
		cam->rotate(0,pitch);
		auto mat = mGhost->getWorldTransform().getBasis();
		auto strafe = mat[0];
		strafe = strafe.normalize();
		mat *= btMatrix3x3(btQuaternion(btVector3(0,1,0), yaw));
		mGhost->getWorldTransform().setBasis(mat);

		//mat *= btMatrix3x3(btQuaternion(strafe, pitch));
		auto btquat =  btQuaternion(strafe, pitch);
		Quaternion q = Quaternion(btquat.getW(), btquat.getX(), btquat.getY(), btquat.getZ());
		//Handles yaw
		cam->forward = Vector4(mat[2].x(), mat[2].y(), mat[2].z(), 0);
		//cam->up = glm::normalize(cam->up*q);
		//mGhost->getWorldTransform().setBasis(mat);
		//auto yawQbt= btQuaternion(btVector3(0, 1, 0), yaw);
		//Quaternion yawQ = Quaternion(yawQbt.getW(), yawQbt.getX(), yawQbt.getY(), yawQbt.getZ());
		//cam->forward =  q* Vector4(mat[2].x(), mat[2].y(), mat[2].z(), 0) + cam->forward;
		//cam->up = q*cam->up + glm::normalize(Vector4(mat[1].x(), mat[1].y(), mat[1].z(), 0));
		//TODO figure out how to make camera pitching work correctly. Until then, just pitch the dude
		//auto cam = mOwner->get_component<CameraComponent>(ComponentType::Camera);
		//Vector4 up ={0,1,0,0};
		//up = Quaternion(cam->mTransform->get_transform())*up;
		//up = glm::normalize(up);
		//if (up.y > 0.15) {
		//	cam->mTransform->rotate_axis({ strafe.x(), strafe.y(), strafe.z() }, pitch*100);
		//} else {
		//	if(pitch < 0)
		//		cam->mTransform->rotate_axis({ strafe.x(), strafe.y(), strafe.z() }, 0.1);
		//	else
		//		cam->mTransform->rotate_axis({ strafe.x(), strafe.y(), strafe.z() }, -0.1);
		//}

	
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