#include "epch.h"
#include "Transform.h"

#include <math.h>

namespace Cherry
{
	TransformationMatrix::TransformationMatrix(float x, float y)
	{
		SetIdentity();
		columns[3].x = x;
		columns[3].y = y;
	}

	TransformationMatrix::TransformationMatrix(Vector2f pos)
	{
		SetIdentity();
		columns[3].x = pos.x;
		columns[3].y = pos.y;
	}

	void TransformationMatrix::Translate(Vector2f translation)
	{
		columns[3].x += translation.x;
		columns[3].y += translation.y;
	}

	void TransformationMatrix::Rotate(float rotation)
	{
		Matrix4x4f rotate = Matrix4x4f::Identity();

		rotate[0].x = cos(rotation * 3.14159265 / 180);
		rotate[0].y = -sin(rotation * 3.14159265 / 180);
		rotate[1].x = sin(rotation * 3.14159265 / 180);
		rotate[1].y = cos(rotation * 3.14159265 / 180);

		*this = *this * rotate;
	}

	void TransformationMatrix::Scale(Vector2f scalar)
	{
		Matrix4x4f scale = Matrix4x4f::Identity();
		scale[0].x = scalar.x;
		scale[1].y = scalar.y;

		*this = *this * scale;
	}

	void TransformationMatrix::Scale(float scalar)
	{
		columns[0].x = scalar;
		columns[1].y = scalar;
	}

	void TransformationMatrix::operator=(Matrix4x4f mat)
	{
		columns[0] = mat[0];
		columns[1] = mat[1];
		columns[2] = mat[2];
		columns[3] = mat[3];
	};
}
