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

	TransformationMatrix::TransformationMatrix(const Vector2f& pos)
	{
		SetIdentity();
		columns[3].x = pos.x;
		columns[3].y = pos.y;
	}

	void TransformationMatrix::Translate(const Vector2f& translation)
	{
		columns[3].x += translation.x;
		columns[3].y += translation.y;

		m_Translation += translation;
	}

	void TransformationMatrix::Rotate(float rotation)
	{

		float rotInRadians = rotation * 0.0174533;
		float rotCos = cos(rotInRadians);
		float rotSin = sin(rotInRadians);

		float val00 = rotCos * columns[0].x +
					  -rotSin * columns[1].x;

		float val01 = rotCos * columns[0].y +
					  -rotSin * columns[1].y;

		float val10 = rotSin * columns[0].x +
					  rotCos * columns[1].x;

		float val11 = rotSin * columns[0].y +
					  rotCos * columns[1].y;

		columns[0].x = val00;
		columns[0].y = val01;
		columns[1].x = val10;
		columns[1].y = val11;


		m_Rotation += rotation;
	}

	void TransformationMatrix::Scale(const Vector2f& scalar)
	{
		columns[0].x *= scalar.x;
		columns[1].y *= scalar.y;

		m_Scale += scalar;
	}

	void TransformationMatrix::Scale(float scalar)
	{
		columns[0].x *= scalar;
		columns[1].y *= scalar;

		m_Scale += scalar;
	}

	void TransformationMatrix::SetTranslation(Vector2f translation)
	{
		columns[3][0] = translation.x;
		columns[3][1] = translation.y;

		m_Translation = translation;
	}

	// TODO: Optimize TransformationMatrix::SetRotation() and TransformationMatrix::SetScale()
	void TransformationMatrix::SetRotation(float rotation)
	{
		SetIdentity();
		columns[3][0] = m_Translation.x;
		columns[3][1] = m_Translation.y;

		columns[0][0] = m_Scale.x;
		columns[1][1] = m_Scale.y;

		Matrix4x4f rotate = Matrix4x4f::Identity();
		rotate[0].x = rotation;
		rotate[1].y = rotation;

		*this = (Matrix4x4f)*this * rotate;
	}

	void TransformationMatrix::SetScale(Vector2f scalar)
	{
		SetIdentity();
		columns[3][0] = m_Translation.x;
		columns[3][1] = m_Translation.y;

		columns[0].x =  cos(m_Rotation * 3.14159265 / 180);
		columns[0].y = -sin(m_Rotation * 3.14159265 / 180);
		columns[1].x =  sin(m_Rotation * 3.14159265 / 180);
		columns[1].y =  cos(m_Rotation * 3.14159265 / 180);

		Matrix4x4f scale = Matrix4x4f::Identity();
		scale[0].x = scalar.x;
		scale[1].y = scalar.y;

		*this = (Matrix4x4f)*this * scale;
	}

	void TransformationMatrix::SetScale(float scalar)
	{
		SetIdentity();
		columns[3][0] = m_Translation.x;
		columns[3][1] = m_Translation.y;

		columns[0].x = cos(m_Rotation * 3.14159265 / 180);
		columns[0].y = -sin(m_Rotation * 3.14159265 / 180);
		columns[1].x = sin(m_Rotation * 3.14159265 / 180);
		columns[1].y = cos(m_Rotation * 3.14159265 / 180);

		Matrix4x4f scale = Matrix4x4f::Identity();
		scale[0].x = scalar;
		scale[1].y = scalar;

		*this = (Matrix4x4f)*this * scale;
	}

	void TransformationMatrix::operator=(Matrix4x4f mat)
	{
		columns[0] = mat[0];
		columns[1] = mat[1];
		columns[2] = mat[2];
		columns[3] = mat[3];
	}

	Vector4f TransformationMatrix::operator*(Vector4f vec)
	{
		return columns[0] * vec[0]
			+ columns[1] * vec[1]
			+ columns[2] * vec[2]
			+ columns[3] * vec[3];
	}
	
	void CHERRY_API Translate(Matrix4x4f* mat, float x, float y)
	{
		(*mat)[3].x += x;
		(*mat)[3].y += y;
	}

	void CHERRY_API Rotate(Matrix4x4f* mat, float rot)
	{
		float rotInRadians = rot * 0.0174533;
		float rotCos = cos(rotInRadians);
		float rotSin = sin(rotInRadians);

		float val00 = rotCos * (*mat)[0].x +
					  -rotSin * (*mat)[1].x;

		float val01 = rotCos * (*mat)[0].y +
					  -rotSin * (*mat)[1].y;

		float val10 = rotSin * (*mat)[0].x +
					  rotCos * (*mat)[1].x;

		float val11 = rotSin * (*mat)[0].y +
					  rotCos * (*mat)[1].y;

		(*mat)[0].x = val00;
		(*mat)[0].y = val01;
		(*mat)[1].x = val10;
		(*mat)[1].y = val11;
	}

	void CHERRY_API Scale(Matrix4x4f* mat, float scale)
	{
		(*mat)[0].x *= scale;
		(*mat)[1].y *= scale;
	}

	void CHERRY_API Scale(Matrix4x4f* mat, float scaleX, float scaleY)
	{
		(*mat)[0].x *= scaleX;
		(*mat)[1].y *= scaleY;
	}

}
