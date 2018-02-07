#include <transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/matrix_interpolation.hpp>
#include <glm/gtx/transform.hpp>
namespace Aurora {
	/**
	Constructs a Transform Object
	*/

	Transform::Transform(): mParent(nullptr), mTranslation(Vector3()), mRotation(Quaternion()), mScale(Vector3(1.0, 1.0, 1.0)) {}
	Transform::~Transform() {}
	/**
	Get the transform in matrix form
	@returns A 4x4 homogenous matrix of floats in column Major order representing the transformation in world coordinates
	*/

	Matrix4 Transform::get_transform() const {
		Matrix4 rot = glm::mat4_cast(mRotation);
		Matrix4 scale = glm::scale(mScale);
		Matrix4 translation = glm::translate(mTranslation);
		if (mParent)
			return get_parent_transforms(mParent) * translation * rot * scale;
		else
			return translation * rot * scale;
	}

	Matrix4 Transform::get_local_transform() const {
		Matrix4 rot = glm::mat4_cast(mRotation);
		Matrix4 scale = glm::scale(mScale);
		Matrix4 translation = glm::translate(mTranslation);
		return translation * rot * scale;
	}
	Matrix4 Transform::get_parent_transforms(Transform* parent) const {
		return parent->get_transform();
	}

	/**
	Sets the translation in world coordinates
	@param x The x value of the transformation
	@param y The y value of the transformation
	@param z The z value of the transformation
	*/

	void Transform::set_translation(const float x, const float y, const float z) {
		mTranslation.x = x;
		mTranslation.y = y;
		mTranslation.z = z;
	}

	/**
	Sets the translation in world coordinates
	@param translation The xyz values of the transformation
	*/

	void Transform::set_translation(Vector3 translation) {
		mTranslation = translation;
	}

	/**
	Sets the uniform scale. Will scale equally in all directions
	@param xyz The scaling factor
	*/

	void Transform::set_scale(const float xyz) {
		mScale.x = xyz;
		mScale.y = xyz;
		mScale.z = xyz;
	}

	/*
	Sets the scale. This should be used only for non uniform scaling
	@param x The x direction scaling factor
	@param y The y direction scaling factor
	@param z The z direction scaling factor
	*/

	void Transform::set_scale(const float x, const float y, const float z) {
		mScale.x = x;
		mScale.y = y;
		mScale.z = z;
	}

	/**
	Sets the scale by a vector instead of individual components
	@param scale The scaling factors
	*/

	void Transform::set_scale(Vector3 scale) {
		mScale = scale;
	}

	void Transform::scale(const float xyz) {
		mScale += xyz;
	}

	/**
	Sets the rotation using Euler angles. This uses a Quaternion internally. User facing euler angles are expected however.
	@param x The rotation in degrees in the x direction
	@param y The rotation in degrees in the y direction
	@param z The rotation in degrees in the z direction
	*/

	void Transform::set_rotation(const float x, const float y, const float z) {

		mRotation = Quaternion(Vector3(glm::radians(x), glm::radians(y), glm::radians(z)));
	}

	void Transform::set_rotation(const Quaternion q) {
		mRotation = q;
	}

	/**
	Sets the rotation using Euler angles. This uses a Quaternion internally. User facing euler angles are expected however.
	@param rot The rotation in degrees in the xyz directions in radians
	*/

	void Transform::set_rotation(Vector3 rot) {
		set_rotation(rot.x, rot.y, rot.z);
	}

	void Transform::rotate_x(float degrees) {
		mRotation = glm::angleAxis(glm::radians(degrees), glm::vec3(1.0f, 0.0f, 0.0f))*mRotation;
	}

	void Transform::rotate_y(float degrees) {
		mRotation = glm::angleAxis(glm::radians(degrees), glm::vec3(0.0f, 1.0f, 0.0f))*mRotation;
	}

	void Transform::rotate_z(float degrees) {
		mRotation = glm::angleAxis(glm::radians(degrees), glm::vec3(0.0f, 0.0f, 1.0f))*mRotation;
	}
	void Transform::rotate_axis(Vector3 axis, float degrees) {

		mRotation = glm::angleAxis(glm::radians(degrees), axis)*mRotation;
	}

	void Transform::translate(const float x, const float y, const float z) {
		mTranslation += Vector3(x, y, z);
	}

	void Transform::transform_by(Matrix4 trans) {
		auto transform = trans * get_local_transform();
		glm::vec3 scale;
		glm::quat rotation;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(transform, scale, rotation, translation, skew, perspective);
		set_scale(scale);
		set_translation(translation);
		set_rotation(rotation);
	}
	void Transform::look_at(Vector3 point, Vector3 up) {

	}
}
