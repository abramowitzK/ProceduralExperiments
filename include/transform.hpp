#ifndef CBLOCKS_TRANSFORM_HPP
#define CBLOCKS_TRANSFORM_HPP


#include <glm\mat4x4.hpp>
#include <glm\vec4.hpp>
#include <glm\vec3.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\matrix_interpolation.hpp>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
namespace CBlocks {
	/**
	This is an opengl compatible matrix from glm.
	*/
	typedef glm::mat4 Matrix4;
	typedef glm::vec4 Vector4;
	typedef glm::quat Quaternion;
	typedef glm::vec3 Vector3;
	typedef glm::vec2 Vector2;

	/**
	Purpose: Represents the transformation of a game object. Every game object is required to have
	a transform so therefore I will not make it a subclass of Component;
	*/
	class Transform final {
	public:
		/**
		Constructs a Transform Object
		*/
		Transform() : m_parent(nullptr), m_translation(Vector3()), m_rotation(Quaternion()), m_scale(Vector3()) {}
		~Transform() {}

		/**
		Get the transform in matrix form
		@returns A 4x4 homogenous matrix of floats in column Major order representing the transformation in world coordinates
		*/
		inline Matrix4 GetTransform() const {
			Matrix4 rot = glm::mat4_cast(m_rotation);
			Matrix4 scale = glm::scale(m_scale);
			Matrix4 translation = glm::translate(m_translation);
			Matrix4 identity = Matrix4(1.0);
			return scale * rot * translation * identity;
		}
		/**
		Sets the translation in world coordinates
		@param x The x value of the transformation
		@param y The y value of the transformation
		@param z The z value of the transformation
		*/
		inline void SetTranslation(const float x, const float y, const float z) {
			m_translation.x = x;
			m_translation.y = y;
			m_translation.z = z;
		}
		/**
		Sets the uniform scale. Will scale equally in all directions
		@param xyz The scaling factor
		*/
		inline void SetScale(const float xyz) {
			m_scale.x = xyz;
			m_scale.y = xyz;
			m_scale.z = xyz;
		}
		/*
		Sets the scale. This should be used only for non uniform scaling
		@param x The x direction scaling factor
		@param y The y direction scaling factor
		@param z The z direction scaling factor
		*/
		inline void SetScale(const float x, const float y, const float z) {
			m_scale.x = x;
			m_scale.y = y;
			m_scale.z = z;
		}
		/**
		Sets the rotation using Euler angles. This uses a Quaternion internally. User facing euler angles are expected however.
		@param x The rotation in degrees in the x direction
		@param y The rotation in degrees in the y direction
		@param z The rotation in degrees in the z direction
		*/
		inline void SetRotation(const float x, const float y, const float z) {
			m_rotation = Quaternion(Vector3(x, y, z));
		}

		inline void Translate(const float x, const float y, const float z) {
			m_translation += Vector3(x, y, z);
		}
		inline Vector3 GetPosition() const {
			return m_translation;
		}
		inline Vector3 GetScale() const {
			return m_scale;
		}
		inline Quaternion GetRotation() const {
			return m_rotation;
		}
	private:
		Transform* m_parent;
		Vector3 m_translation;
		Quaternion m_rotation;
		Vector3 m_scale;
	};
}

#endif // !CBLOCKS_TRANSFORM_HPP

