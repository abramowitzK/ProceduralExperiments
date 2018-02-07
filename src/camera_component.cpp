#include "camera_component.hpp"
#include <transform.hpp>
#include <glm\gtx\matrix_decompose.hpp>
#include <game_object.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <vector_math.hpp>
#include <events.hpp>
Aurora::CameraComponent::CameraComponent(int w, int h) {
	mType = ComponentType::Camera;
	EventManager::subscribe_to_resize_event([=](int width, int height) {
		proj = glm::perspective(70.0f, (float)width / (float)height, 0.1f, 10000.0f);
	});
	up = {0,1,0,0};
	forward = {0,0,1,0};
	rotation = {0,0};
	proj = glm::perspective(70.0f, (float)w / (float)h, 0.1f, 10000.0f);
}

void Aurora::CameraComponent::rotate(float yaw, float pitch) {
	rotation.x += yaw;
	rotation.y += pitch;
	auto right = -glm::cross(Vector3(up), Vector3(forward));
	auto quaternion = glm::angleAxis(rotation.y, right);
	auto upVector = glm::normalize(quaternion*up);
	while (fabs(upVector.y) < 0.4) {
		if (glm::dot(upVector, forward) > 0)
			rotation.y += 0.001;
		else
			rotation.y -= 0.001;
		right = -glm::cross(Vector3(up), Vector3(forward));
		quaternion = glm::angleAxis(rotation.y, right);
		upVector = glm::normalize(quaternion*up);
	}

}
void Aurora::CameraComponent::update(double dt) {
	//Vector4 upVector;
	//Matrix4 transform = mTransform->get_transform();
	//Quaternion rot;
	//Vector3 translation;
	//Vector3 skew;
	//Vector4 perspective;
	//Vector3 scale;
	//glm::decompose(transform, scale, rot, translation, skew, perspective);
	//Matrix4 rotationMatrix = Matrix4(rot);
}

void Aurora::CameraComponent::render(Renderer * renderer) {
	//Vector4 upVector, positionVector, lookAtVector;
	//Matrix4 parent = mTransform->mParent->get_transform();
	//Matrix4 local = mTransform->get_local_transform();
	Matrix4 transform = mTransform->get_transform();
	Quaternion rot;
	Vector3 translation;
	Vector3 skew;
	Vector4 perspective;
	Vector3 scale;
	glm::decompose(transform, scale, rot, translation, skew, perspective);
	//Matrix4 rotationMatrix = glm::extractMatrixRotation(local);
	////// Setup the vector that points upwards.
	////up.x = 0.0f;
	////up.y = 1.0f;
	////up.z = 0.0f;

	//// Load it into a XMVECTOR structure.
	//upVector = up;

	//// Setup the position of the camera in the world.
	//// Load it into a XMVECTOR structure.
	//positionVector = Vector4(translation, 0.0);

	////// Setup where the camera is looking by default.
	////forward.x = 0.0f;
	////forward.y = 0.0f;
	////forward.z = 1.0f;

	//// Load it into a XMVECTOR structure.
	//lookAtVector = forward;

	//// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	////lookAtVector = XMVector3Normalize( XMVector3TransformCoord(lookAtVector, rotationMatrix));
	////lookAtVector = glm::normalize(rotationMatrix*lookAtVector);
	////upVector = XMVector3Normalize(XMVector3TransformCoord(upVector, rotationMatrix));
	////upVector = glm::normalize(rotationMatrix*up);
	////lookAtVector = glm::normalize(rot*lookAtVector);

	//// Translate the rotated camera position to the location of the viewer.
	//lookAtVector = positionVector + forward;
	////upVector = rot*upVector;
	//// Finally create the view matrix from the three updated vectors.
	////m_viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
	//view = glm::lookAt(glm::vec3(positionVector), glm::vec3(lookAtVector), glm::vec3(upVector));
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
	positionVector = Vector4(translation, 0);

	//// Setup where the camera is looking by default.
	//forward.x = 0.0f;
	//forward.y = 0.0f;
	//forward.z = 1.0f;

	// Load it into a XMVECTOR structure.
	lookAtVector = forward;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = rotation.y;
	auto right = -glm::cross(Vector3(up), Vector3(forward));
	// Create the rotation matrix from the yaw, pitch, and roll values.
	//rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
	auto quaternion = glm::angleAxis(pitch, right);//glm::eulerAngleYXZ(glm::radians(0.0f), glm::radians(0.0f), glm::radians(pitch));
	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	//lookAtVector = XMVector3Normalize( XMVector3TransformCoord(lookAtVector, rotationMatrix));
	lookAtVector = glm::normalize(quaternion*lookAtVector);
	//forward = glmlookAtVector;
	//upVector = XMVector3Normalize(XMVector3TransformCoord(upVector, rotationMatrix));
	upVector = glm::normalize(quaternion*upVector);
	// Translate the rotated camera position to the location of the viewer.
	lookAtVector = positionVector + lookAtVector;

	// Finally create the view matrix from the three updated vectors.
	//m_viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
	view = glm::lookAt(glm::vec3(positionVector), glm::vec3(lookAtVector), glm::vec3(up));
}
