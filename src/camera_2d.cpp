#include "camera_2d.hpp"
#include <events.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>
#include <vector_math.hpp>
namespace Aurora {
Camera2D::Camera2D(int w, int h) {
    EventManager::subscribe_to_resize_event([=](int width, int height) {
        projection =
            glm::ortho(70.0f, (float)width / (float)height, 0.1f, 10000.0f);
    });
    position   = {0, 0, 0, 1};
    forward    = {0, 0, 1, 1};
    rotation   = {0, 0, 0, 1};
    projection = glm::ortho(70.0f, (float)w / (float)h, 0.1f, 10000.0f);
    velocity   = {0.f, 0.f, 0.f, 1.0f};
}
void Camera2D::update(double dt) {}
void Camera2D::render() {
    Vector4 upVector, positionVector, lookAtVector;
    float   yaw, pitch, roll;
    Matrix4 rotationMatrix;

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

    // Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in
    // radians.
    pitch = rotation.x;
    yaw   = rotation.y;
    roll  = rotation.z;

    // Create the rotation matrix from the yaw, pitch, and roll values.
    // rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
    rotationMatrix = glm::eulerAngleYXZ(glm::radians(yaw), glm::radians(pitch),
                                        glm::radians(roll));
    // Transform the lookAt and up vector by the rotation matrix so the view is
    // correctly rotated at the origin.
    // lookAtVector = XMVector3Normalize( XMVector3TransformCoord(lookAtVector,
    // rotationMatrix));
    lookAtVector = glm::normalize(rotationMatrix * lookAtVector);
    forward      = lookAtVector;
    // upVector = XMVector3Normalize(XMVector3TransformCoord(upVector,
    // rotationMatrix));
    upVector = glm::normalize(rotationMatrix * upVector);
    // Translate the rotated camera position to the location of the viewer.
    lookAtVector = positionVector + lookAtVector;

    // Finally create the view matrix from the three updated vectors.
    // m_viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
    view = glm::lookAt(glm::vec3(positionVector), glm::vec3(lookAtVector),
                       glm::vec3(upVector));
}
} // namespace Aurora
