/*
* Created by Kyle on 12/11/2016.
* Copyright (c) 2016 Kyle All rights reserved.
*/

#include <glm/gtc/constants.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "camera.hpp"
namespace CBlocks {
	Camera::Camera(EventManager& manager, int w, int h) {
		manager.subscribe_to_resize_event([=](int width, int height){
			glm::perspective(70.0f, (float)width/(float)height, 0.1f, 1000.0f);
		});
		position = {0,0,0,1};
		up = {0,0,0,1};
		forward = {0,0,1,1};
		rotation = {0,0,0,1};
		projection = glm::perspective(70.0f, (float)w/(float)h, 0.1f, 1000.0f);
		acceleration = 1.0f;
		speed = 10.0f;
		velocity = { 0.f,0.f,0.f,1.0f};
	}
	void Camera::update(float dt) {
		if(EventManager::get_key_down(Keys::w))
			position += forward*dt*acceleration*speed;
		if (EventManager::get_key_down(Keys::a))
			position -= glm::vec4(glm::normalize(glm::cross(glm::vec3(forward), glm::vec3(up))), 1.0f)*dt*acceleration*speed;
		if (EventManager::get_key_down(Keys::d))
			position += glm::vec4(glm::normalize(glm::cross(glm::vec3(forward), glm::vec3(up))), 1.0f)*dt*acceleration*speed;
		if (EventManager::get_key_down(Keys::s))
			position -= forward*dt*acceleration*speed;
		//if (abs(velocity.x) < acceleration)
		//	velocity.x = 0;
		//else
		//	velocity.x -= acceleration;
		//if (abs(velocity.y) < acceleration)
		//	velocity.y = 0;
		//else
		//	velocity.y -= acceleration;
		//if (abs(velocity.z) < acceleration)
		//	velocity.z = 0;
		//else
		//	velocity.z -= acceleration;
		auto look_x = EventManager::get_mouse_relative_x()/9.0*2.0*glm::pi<float>()*4.0f;
		auto look_y = EventManager::get_mouse_relative_y()/9.0*2.0*glm::pi<float>()*4.0f;

		Vector2 now = {look_x, look_y};
		now = glm::lerp(mPrevMouseTarget, now, 0.9f);
		rotation.x += now.y / 100.0f;
		rotation.y -= now.x / 100.0f;
		mPrevMouseTarget = {now.x, now.y};


	}
	void Camera::render(){

		Vector4 upVector, positionVector, lookAtVector;
		float yaw, pitch, roll;
		Matrix4 rotationMatrix;


		// Setup the vector that points upwards.
		up.x = 0.0f;
		up.y = 1.0f;
		up.z = 0.0f;

		// Load it into a XMVECTOR structure.
		upVector = up;

		// Setup the position of the camera in the world.
		// Load it into a XMVECTOR structure.
		positionVector = position;

		// Setup where the camera is looking by default.
		forward.x = 0.0f;
		forward.y = 0.0f;
		forward.z = 1.0f;

		// Load it into a XMVECTOR structure.
		lookAtVector = forward;

		// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
		pitch = rotation.x;
		yaw = rotation.y;
		roll = rotation.z;

		// Create the rotation matrix from the yaw, pitch, and roll values.
		//rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
		rotationMatrix = glm::eulerAngleYXZ(glm::radians(yaw), glm::radians(pitch), glm::radians(roll));
		// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
		//lookAtVector = XMVector3Normalize( XMVector3TransformCoord(lookAtVector, rotationMatrix));
		lookAtVector = glm::normalize(rotationMatrix*lookAtVector);
		forward = lookAtVector;
		//upVector = XMVector3Normalize(XMVector3TransformCoord(upVector, rotationMatrix));
		upVector = glm::normalize(rotationMatrix*upVector);
		// Translate the rotated camera position to the location of the viewer.
		lookAtVector = positionVector + lookAtVector;

		// Finally create the view matrix from the three updated vectors.
		//m_viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
		view = glm::lookAt(glm::vec3(positionVector), glm::vec3(lookAtVector), glm::vec3(upVector));
	}
}
