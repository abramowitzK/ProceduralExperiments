#include <transform.hpp>
namespace CBlocks {
	 void Transform::expose_to_script() {
		auto m = ScriptManager::instance();
		auto l = m->get_lua_state();
		//Need to disambiguate the overloads so we take the address of the right function
		//l->new_simple_usertype<Transform>("Transform", 
		//	"set_translation", static_cast<void (Transform::*)(const float x, const float y, const float z)>(&Transform::set_translation), 
		//	"set_scale", &Transform::set_scale
		//	);
		//TODO make each class make it's own transform type and then register them all in one place instead of doing the registering in each file.
		sol::usertype<Transform> transformType{
			"scale", &Transform::scale,
			"rotate_x", &Transform::rotate_x,
			"rotate_y", &Transform::rotate_y,
			"rotate_z", &Transform::rotate_z,
			"translation", sol::property(&Transform::mTranslation, &Transform::mTranslation),
			"rotation", sol::property(&Transform::mRotation, &Transform::mRotation),
			"scale", sol::property(&Transform::mScale, &Transform::mScale)
		};
		sol::constructors<sol::types<>, sol::types<float>, sol::types<float, float>> vector2Constructors;
		sol::constructors<sol::types<>, sol::types<float>, sol::types<float, float, float>> vector3Constructors;
		sol::constructors<sol::types<>, sol::types<float>, sol::types<float, float, float, float>> vector4Constructors;
		sol::usertype<Vector2> vector2Type{
			vector2Constructors,
			"x", sol::property(&Vector2::x, &Vector2::x),
			"y", sol::property(&Vector2::y, &Vector2::y),
		};
		sol::usertype<Vector3> vector3Type{
			vector3Constructors,
			"x", sol::property(&Vector3::x, &Vector3::x),
			"y", sol::property(&Vector3::y, &Vector3::y),
			"z", sol::property(&Vector3::z, &Vector3::z),
		};
		sol::usertype<Vector4> vector4Type{
			vector4Constructors,
			"x", sol::property(&Vector4::x, &Vector4::x),
			"y", sol::property(&Vector4::y, &Vector4::y),
			"z", sol::property(&Vector4::z, &Vector4::z),
			"w", sol::property(&Vector4::w, &Vector4::w)
		};
		sol::usertype<Quaternion> quatType{
			"x", sol::property(&Quaternion::x, &Quaternion::x),
			"y", sol::property(&Quaternion::y, &Quaternion::y),
			"z", sol::property(&Quaternion::z, &Quaternion::z),
			"w", sol::property(&Quaternion::w, &Quaternion::w),
			"length", &Quaternion::length,
			"rotate_by", &multiply,
		};
		l->set_usertype("Vector2", vector2Type);
		l->set_usertype("Vector3", vector3Type);
		l->set_usertype("Vector4", vector4Type);
		l->set_usertype("Quaternion", quatType);
		l->set_usertype("Transform", transformType);

	}

	/**
	Constructs a Transform Object
	*/

	 Transform::Transform() : mParent(nullptr), mTranslation(Vector3()), mRotation(Quaternion()), mScale(Vector3(1.0, 1.0, 1.0)) {}

	 Transform::~Transform() {}

	/**
	Get the transform in matrix form
	@returns A 4x4 homogenous matrix of floats in column Major order representing the transformation in world coordinates
	*/

	 Matrix4 Transform::get_transform() const {
		Matrix4 rot = glm::mat4_cast(mRotation);
		Matrix4 scale = glm::scale(mScale);
		Matrix4 translation = glm::translate(mTranslation);
		return translation * rot * scale;
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

	 void Transform::translate(const float x, const float y, const float z) {
		mTranslation += Vector3(x, y, z);
	}
}
