#include "camera_component.hpp"
#include <transform.hpp>
#include <glm\gtx\matrix_decompose.hpp>
Aurora::CameraComponent::CameraComponent(int w, int h, EventManager & manager) {
	mType = ComponentType::Camera;
	manager.subscribe_to_resize_event([=](int width, int height) {
		proj = glm::perspective(70.0f, (float)width/(float)height, 0.1f, 10000.0f);
	});
	up ={ 0,1,0,0 };
	forward ={ 0,0,1,0 };
	proj = glm::perspective(70.0f, (float)w/(float)h, 0.1f, 10000.0f);
}

void Aurora::CameraComponent::expose_to_script() {}

void Aurora::CameraComponent::update(double dt) {

}

void Aurora::CameraComponent::render(Renderer * renderer) {
	Vector4 upVector, positionVector, lookAtVector;
	Matrix4 transform = mTransform->get_transform();
	Quaternion rot;
	Vector3 translation;
	Vector3 skew;
	Vector4 perspective;
	Vector3 scale;
	glm::decompose(transform, scale, rot, translation, skew, perspective);
	Matrix4 rotationMatrix = Matrix4(rot);

	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Load it into a XMVECTOR structure.
	upVector = up;

	// Setup the position of the camera in the world.
	// Load it into a XMVECTOR structure.
	positionVector = Vector4(translation, 1.0);

	// Setup where the camera is looking by default.
	forward.x = 0.0f;
	forward.y = 0.0f;
	forward.z = 1.0f;

	// Load it into a XMVECTOR structure.
	lookAtVector = forward;

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	//lookAtVector = XMVector3Normalize( XMVector3TransformCoord(lookAtVector, rotationMatrix));
	lookAtVector = glm::normalize(rotationMatrix*lookAtVector);
	forward = lookAtVector;
	//upVector = XMVector3Normalize(XMVector3TransformCoord(upVector, rotationMatrix));
	upVector = glm::normalize(rotationMatrix*up);
	// Translate the rotated camera position to the location of the viewer.
	lookAtVector = positionVector + lookAtVector;

	// Finally create the view matrix from the three updated vectors.
	//m_viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
	view = glm::lookAt(glm::vec3(positionVector), glm::vec3(lookAtVector), glm::vec3(upVector));
}
