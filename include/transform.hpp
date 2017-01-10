#ifndef CBLOCKS_TRANSFORM_HPP
#define CBLOCKS_TRANSFORM_HPP


#include <glm\mat4x4.hpp>
#include <glm\vec4.hpp>
#include <glm\vec3.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\matrix_interpolation.hpp>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <vector_math.hpp>
#include <script_manager.hpp>
namespace CBlocks {


	/**
	Purpose: Represents the transformation of a game object. Every game object is required to have
	a transform so therefore I will not make it a subclass of Component;
	*/
	class Transform {
	public:
		static void expose_to_script() {
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
				"rotate_y", &Transform::rotate_y
			};
			l->set_usertype("Transform", transformType);
			sol::usertype<Vector3> vector3Type{
				"x", sol::property(&Vector3::x, &Vector3::x),
				"y", sol::property(&Vector3::y, &Vector3::y),
				"z", sol::property(&Vector3::z, &Vector3::z),
			};
			sol::usertype<Quaternion> quatType{
				"x", sol::property(&Quaternion::x, &Quaternion::x),
				"y", sol::property(&Quaternion::y, &Quaternion::y),
				"z", sol::property(&Quaternion::z, &Quaternion::z),
				"w", sol::property(&Quaternion::w, &Quaternion::w),
				"length", &Quaternion::length
			};
			l->set_usertype("Vector3", vector3Type);


		}
		/**
		Constructs a Transform Object
		*/
		Transform() : mParent(nullptr), mTranslation(Vector3()), mRotation(Quaternion()), mScale(Vector3(1.0, 1.0,1.0)) {}
		~Transform() {}
		/**
		Get the transform in matrix form
		@returns A 4x4 homogenous matrix of floats in column Major order representing the transformation in world coordinates
		*/
		inline Matrix4 GetTransform() const {
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
		inline void set_translation(const float x, const float y, const float z) {
			mTranslation.x = x;
			mTranslation.y = y;
			mTranslation.z = z;
		}
		/**
		Sets the translation in world coordinates
		@param translation The xyz values of the transformation
		*/
		inline void set_translation(Vector3 translation) {
			mTranslation = translation;
		}
		/**
		Sets the uniform scale. Will scale equally in all directions
		@param xyz The scaling factor
		*/
		inline void set_scale(const float xyz) {
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
		inline void set_scale(const float x, const float y, const float z) {
			mScale.x = x;
			mScale.y = y;
			mScale.z = z;
		}
		/**
		Sets the scale by a vector instead of individual components
		@param scale The scaling factors
		*/
		inline void set_scale(Vector3 scale) {
			mScale = scale;
		}
		inline void scale(const float xyz) {
			mScale += xyz;
		}
		/**
		Sets the rotation using Euler angles. This uses a Quaternion internally. User facing euler angles are expected however.
		@param x The rotation in degrees in the x direction
		@param y The rotation in degrees in the y direction
		@param z The rotation in degrees in the z direction
		*/
		inline void set_rotation(const float x, const float y, const float z) {
			
			mRotation = Quaternion(Vector3(glm::radians(x), glm::radians(y), glm::radians(z)));
		}
		inline void set_rotation(const Quaternion q) {
			mRotation = q;
		}
		/**
		Sets the rotation using Euler angles. This uses a Quaternion internally. User facing euler angles are expected however.
		@param rot The rotation in degrees in the xyz directions in radians
		*/
		inline void set_rotation(Vector3 rot) {
			set_rotation(rot.x, rot.y, rot.z);
		}
		inline void rotate_x(float degrees) {
			mRotation = glm::angleAxis(glm::radians(degrees), glm::vec3(1.0f, 0.0f, 0.0f))*mRotation;
		}
		inline void rotate_y(float degrees) {
			mRotation = glm::angleAxis(glm::radians(degrees), glm::vec3(0.0f, 1.0f, 0.0f))*mRotation;
		}
		inline void rotate_z(float degrees) {
			mRotation = glm::angleAxis(glm::radians(degrees), glm::vec3(0.0f, 0.0f, 1.0f))*mRotation;
		}
		inline void translate(const float x, const float y, const float z) {
			mTranslation += Vector3(x, y, z);
		}

		Transform* mParent;
		Vector3 mTranslation;
		Quaternion mRotation;
		Vector3 mScale;
	};
}

#endif // !CBLOCKS_TRANSFORM_HPP

