#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/matrix_interpolation.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector_math.hpp>
#include <script_manager.hpp>
namespace Aurora {

	static Quaternion multiply(Quaternion l, Quaternion r) {
		return r*l;
	}
	/**
	Purpose: Represents the transformation of a game object. Every game object is required to have
	a transform so therefore I will not make it a subclass of Component;
	*/
	class Transform {
	public:
		static void expose_to_script(ScriptManager* m);
		/**
		Constructs a Transform Object
		*/
		Transform();
		~Transform();
		/**
		Get the transform in matrix form
		@returns A 4x4 homogenous matrix of floats in column Major order representing the transformation in world coordinates
		*/
		 Matrix4 get_transform() const;
		 Matrix4 get_parent_transforms(Transform* parent) const;
		/**
		Sets the translation in world coordinates
		@param x The x value of the transformation
		@param y The y value of the transformation
		@param z The z value of the transformation
		*/
		 void set_translation(const float x, const float y, const float z);
		/**
		Sets the translation in world coordinates
		@param translation The xyz values of the transformation
		*/
		 void set_translation(Vector3 translation);
		/**
		Sets the uniform scale. Will scale equally in all directions
		@param xyz The scaling factor
		*/
		 void set_scale(const float xyz);
		/*
		Sets the scale. This should be used only for non uniform scaling
		@param x The x direction scaling factor
		@param y The y direction scaling factor
		@param z The z direction scaling factor
		*/
		 void set_scale(const float x, const float y, const float z);
		/**
		Sets the scale by a vector instead of individual components
		@param scale The scaling factors
		*/
		 void set_scale(Vector3 scale);
		 void scale(const float xyz);
		/**
		Sets the rotation using Euler angles. This uses a Quaternion internally. User facing euler angles are expected however.
		@param x The rotation in degrees in the x direction
		@param y The rotation in degrees in the y direction
		@param z The rotation in degrees in the z direction
		*/
		 void set_rotation(const float x, const float y, const float z);
		 void set_rotation(const Quaternion q);
		/**
		Sets the rotation using Euler angles. This uses a Quaternion internally. User facing euler angles are expected however.
		@param rot The rotation in degrees in the xyz directions in radians
		*/
		 void set_rotation(Vector3 rot);
		 void rotate_x(float degrees);
		 void rotate_y(float degrees);
		 void rotate_z(float degrees);
		 void translate(const float x, const float y, const float z);

		Transform* mParent;
		Vector3 mTranslation;
		Quaternion mRotation;
		Vector3 mScale;
	};
}
