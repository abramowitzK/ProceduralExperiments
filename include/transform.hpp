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
namespace CBlocks {
	/**
	Purpose: Represents the transformation of a game object. Every game object is required to have
	a transform so therefore I will not make it a subclass of Component;
	*/
	class Transform final {
	public:
		/**
		Constructs a Transform Object
		*/
		Transform() : mParent(nullptr), mTranslation(Vector3()), mRotation(Quaternion()), mScale(Vector3()) {}
		~Transform() {}

		/**
		Get the transform in matrix form
		@returns A 4x4 homogenous matrix of floats in column Major order representing the transformation in world coordinates
		*/
		inline Matrix4 GetTransform() const {
			Matrix4 rot = glm::mat4_cast(mRotation);
			Matrix4 scale = glm::scale(mScale);
			Matrix4 translation = glm::translate(mTranslation);
			Matrix4 identity = Matrix4(1.0);
			return scale * rot * translation * identity;
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
		/**
		Sets the rotation using Euler angles. This uses a Quaternion internally. User facing euler angles are expected however.
		@param x The rotation in degrees in the x direction
		@param y The rotation in degrees in the y direction
		@param z The rotation in degrees in the z direction
		*/
		inline void set_rotation(const float x, const float y, const float z) {
			
			mRotation = Quaternion(Vector3(glm::radians(x), glm::radians(y), glm::radians(z)));
		}
		/**
		Sets the rotation using Euler angles. This uses a Quaternion internally. User facing euler angles are expected however.
		@param rot The rotation in degrees in the xyz directions in radians
		*/
		inline void set_rotation(Vector3 rot) {
			mRotation = Quaternion(rot);
		}

		inline void translate(const float x, const float y, const float z) {
			mTranslation += Vector3(x, y, z);
		}
		inline Vector3 get_position() const {
			return mTranslation;
		}
		inline Vector3 get_scale() const {
			return mScale;
		}
		inline Quaternion get_rotation() const {
			return mRotation;
		}
	private:
		Transform* mParent;
		Vector3 mTranslation;
		Quaternion mRotation;
		Vector3 mScale;
	};
}

#endif // !CBLOCKS_TRANSFORM_HPP

