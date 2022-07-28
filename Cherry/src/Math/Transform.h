#pragma once

#include "Matrix.h"
#include "Vector.h"

namespace Cherry
{
	class CHERRY_API TransformationMatrix : public Matrix4x4f
	{
	public:
		TransformationMatrix() { SetIdentity(); };

		TransformationMatrix(float x, float y);
		TransformationMatrix(Vector2f pos);

		void Translate(Vector2f translation);
		void Rotate(float rotation);
		void Scale(Vector2f scalar);
		void Scale(float scalar);

		void operator=(Matrix4x4f mat);
	};
}