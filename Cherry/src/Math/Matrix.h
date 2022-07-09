#pragma once

#include "core/Core.h"
#include "Vector.h"


// TODO: rewrite math library using templates, see glm source
namespace Cherry
{
	class CHERRY_API Matrix2x2
	{
	private:
		Vector2 rows[2];

	public:
		Matrix2x2()
		{
			rows[0] = Vector2();
			rows[1] = Vector2();
		}

		Matrix2x2(
			float m00, float m01, 
			float m10, float m11)
		{
			rows[0] = Vector2(m00, m01);
			rows[1] = Vector2(m10, m11);
		}

		Matrix2x2(Vector2 m0, Vector2 m1)
		{
			rows[0] = m0;
			rows[1] = m1;
		}

		static Matrix2x2 Identity()
		{
			return Matrix2x2(
				1, 0, 
				0, 1
			);
		}

		void SetIdentity()
		{
			rows[0].x = 1;
			rows[0].y = 0;

			rows[1].x = 0;
			rows[1].y = 1;
		}

		Vector2 GetRow(int index)
		{
			return rows[index]
		}

		Vector2 GetColumn(int index)
		{
			return Vector2(rows[0][index], rows[1][index]);
		}

		bool operator==(Matrix2x2 other)
		{
			return rows[0] == other[0] && rows[1] == other[1];
		}

		bool operator!=(Matrix2x2 other)
		{
			return !(rows[0] == other[0] && rows[1] == other[1]);
		}

		Vector2 operator[](int index)
		{
			if (index == 0) return rows[0];
			if (index == 1) return rows[1];

			CH_ERROR("In Matrix2x2::operator[]: Index out of bounds");
		}

		// Addition

		Matrix2x2 operator+(int num)
		{
			return Matrix2x2(rows[0] + num, rows[1] + num);
		}

		Matrix2x2 operator+(float num)
		{
			return Matrix2x2(rows[0] + num, rows[1] + num);
		}

		Matrix2x2 operator+(double num)
		{
			return Matrix2x2(rows[0] + num, rows[1] + num);
		}

		Matrix2x2 operator+(Matrix2x2 mat)
		{
			return Matrix2x2(rows[0] + mat[0], rows[1] + mat[1]);
		}

		void operator+=(int num)
		{
			rows[0] += num;
			rows[1] += num;
		}

		void operator+=(float num)
		{
			rows[0] += num;
			rows[1] += num;
		}

		void operator+=(double num)
		{
			rows[0] += num;
			rows[1] += num;
		}

		void operator+=(Matrix2x2 mat)
		{
			rows[0] += mat[0];
			rows[1] += mat[1];
		}

		// Subtraction

		Matrix2x2 operator-(int num)
		{
			return Matrix2x2(rows[0] - num, rows[1] - num);
		}

		Matrix2x2 operator-(float num)
		{
			return Matrix2x2(rows[0] - num, rows[1] - num);
		}

		Matrix2x2 operator-(double num)
		{
			return Matrix2x2(rows[0] - num, rows[1] - num);
		}

		Matrix2x2 operator-(Matrix2x2 mat)
		{
			return Matrix2x2(rows[0] - mat[0], rows[1] - mat[1]);
		}

		void operator-=(int num)
		{
			rows[0] -= num;
			rows[1] -= num;
		}

		void operator-=(float num)
		{
			rows[0] -= num;
			rows[1] -= num;
		}

		void operator-=(double num)
		{
			rows[0] -= num;
			rows[1] -= num;
		}

		void operator-=(Matrix2x2 mat)
		{
			rows[0] -= mat[0];
			rows[1] -= mat[1];
		}

		// Multiplication

		Matrix2x2 operator*(int num)
		{
			return Matrix2x2(rows[0] * num, rows[1] * num);
		}

		Matrix2x2 operator*(float num)
		{
			return Matrix2x2(rows[0] * num, rows[1] * num);
		}

		Matrix2x2 operator*(double num)
		{
			return Matrix2x2(rows[0] * num, rows[1] * num);
		}

		Vector2 operator*(Vector2 vec)
		{
			return Vector2(rows[0][0], rows[1][0]) * vec[0] + 
				   Vector2(rows[0][1], rows[1][1]) * vec[1];
		}

		Matrix2x2 operator*(Matrix2x2 Mat)
		{
			return Matrix2x2(
				*this * Mat.GetColumn(0),
				*this * Mat.GetColumn(1)
			);
		}

		void operator*=(int other)
		{
			rows[0] *= other;
			rows[1] *= other;
		}

		void operator*=(float other)
		{
			rows[0] *= other;
			rows[1] *= other;
		}

		void operator*=(double other)
		{
			rows[0] *= other;
			rows[1] *= other;
		}

		// TODO: Optimize Matrix2x2::operator*=() and Matrix3x3::operator*=()
		void operator*=(Matrix2x2 other)
		{
			Matrix2x2 mat = *this * other;
			rows[0] = mat[0];
			rows[1] = mat[1];
		}
	};

	class CHERRY_API Matrix3x3
	{
	private:
		Vector3 rows[3];

	public:
		Matrix3x3()
		{
			rows[0] = Vector3();
			rows[1] = Vector3();
			rows[2] = Vector3();
		}

		Matrix3x3(
			float m00, float m01, float m02, 
			float m10, float m11, float m12, 
			float m20, float m21, float m22)
		{
			rows[0] = Vector3(m00, m01, m02);
			rows[1] = Vector3(m10, m11, m12);
			rows[2] = Vector3(m20, m21, m22);
		}

		Matrix3x3(Vector3 m0, Vector3 m1, Vector3 m2)
		{
			rows[0] = m0;
			rows[1] = m1;
			rows[2] = m2;
		}

		static Matrix3x3 Identity()
		{
			return Matrix3x3(
				1, 0, 0, 
				0, 1, 0, 
				0, 0, 1
			);
		}

		void SetIdentity()
		{
			rows[0].x = 1;
			rows[0].y = 0;
			rows[0].z = 0;

			rows[1].x = 0;
			rows[1].y = 1;
			rows[1].z = 0;

			rows[2].x = 0;
			rows[2].y = 0;
			rows[2].z = 1;
		}
		
		Vector3 GetRow(int index)
		{
			return rows[index];
		}

		Vector3 GetColumn(int index)
		{
			return Vector3(rows[0][index], rows[1][index], rows[2][index]);
		}

		Vector3 operator[](int index)
		{
			return rows[index];
		}

		bool operator==(Matrix3x3 other)
		{
			return rows[0] == other[0] && rows[1] == other[1] && rows[2] == other[2];
		}

		bool operator!=(Matrix3x3 other)
		{
			return !(rows[0] == other[0] && rows[1] == other[1] && rows[2] == other[2]);
		}

		// Addition

		Matrix3x3 operator+(int num)
		{
			return Matrix3x3(rows[0] + num, rows[1] + num, rows[2] + num);
		}

		Matrix3x3 operator+(float num)
		{
			return Matrix3x3(rows[0] + num, rows[1] + num, rows[2] + num);
		}

		Matrix3x3 operator+(double num)
		{
			return Matrix3x3(rows[0] + num, rows[1] + num, rows[2] + num);
		}

		Matrix3x3 operator+(Matrix3x3 mat)
		{
			return Matrix3x3(rows[0] + mat[0], rows[1] + mat[1], rows[2] + mat[2]);
		}

		void operator+=(int other)
		{
			rows[0] += other;
			rows[1] += other;
			rows[2] += other;
		}

		void operator+=(float other)
		{
			rows[0] += other;
			rows[1] += other;
			rows[2] += other;
		}

		void operator+=(double other)
		{
			rows[0] += other;
			rows[1] += other;
			rows[2] += other;
		}

		void operator+=(Matrix3x3 other)
		{
			rows[0] += other[0];
			rows[1] += other[1];
			rows[2] += other[2];
		}

		Matrix3x3 operator-(int other)
		{
			return Matrix3x3(rows[0] - other, rows[1] - other, rows[2] - other);
		}

		Matrix3x3 operator-(float other)
		{
			return Matrix3x3(rows[0] - other, rows[1] - other, rows[2] - other);
		}

		Matrix3x3 operator-(double other)
		{
			return Matrix3x3(rows[0] - other, rows[1] - other, rows[2] - other);
		}

		Matrix3x3 operator-(Matrix3x3 other)
		{
			return Matrix3x3(rows[0] - other[0], rows[1] - other[1], rows[2] - other[2]);
		}

		void operator-=(int other)
		{
			rows[0] -= other;
			rows[1] -= other;
			rows[2] -= other;
		}

		void operator-=(float other)
		{
			rows[0] -= other;
			rows[1] -= other;
			rows[2] -= other;
		}

		void operator-=(double other)
		{
			rows[0] -= other;
			rows[1] -= other;
			rows[2] -= other;
		}

		void operator-=(Matrix3x3 other)
		{
			rows[0] -= other[0];
			rows[1] -= other[1];
			rows[2] -= other[2];
		}

		Matrix3x3 operator*(int other)
		{
			return Matrix3x3(rows[0] * other, rows[1] * other, rows[2] * other);
		}

		Matrix3x3 operator*(float other)
		{
			return Matrix3x3(rows[0] * other, rows[1] * other, rows[2] * other);
		}

		Matrix3x3 operator*(double other)
		{
			return Matrix3x3(rows[0] * other, rows[1] * other, rows[2] * other);
		}

		Vector3 operator*(Vector3 vec)
		{
			return Vector3(rows[0][0], rows[1][0], rows[2][0]) * vec[0] +
				Vector3(rows[0][1], rows[1][1], rows[2][1]) * vec[1] +
				Vector3(rows[0][2], rows[1][2], rows[2][2]) * vec[2];
		}

		Matrix3x3 operator*(Matrix3x3 other)
		{
			return Matrix3x3(
				*this * other[0],
				*this * other[1],
				*this * other[2]
			);
		}

		void operator*=(int other)
		{
			rows[0] *= other;
			rows[1] *= other;
			rows[2] *= other;
		}

		void operator*=(float other)
		{
			rows[0] *= other;
			rows[1] *= other;
			rows[2] *= other;
		}

		void operator*=(double other)
		{
			rows[0] *= other;
			rows[1] *= other;
			rows[2] *= other;
		}

		void operator*=(Matrix3x3 other)
		{
			Matrix3x3 mat = *this * other;
			rows[0] *= mat[0];
			rows[1] *= mat[1];
			rows[2] *= mat[2];
		}
	};

	class CHERRY_API Matrix4x4
	{
	private:
		Vector4 rows[4];

	public:
		Matrix4x4()
		{
			rows[0] = Vector4();
			rows[1] = Vector4();
			rows[2] = Vector4();
			rows[3] = Vector4();
		}

		Matrix4x4(
			float m00, float m01, float m02, float m03, 
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33)
		{
			rows[0] = Vector4(m00, m01, m02, m03);
			rows[1] = Vector4(m10, m11, m12, m13);
			rows[2] = Vector4(m20, m21, m22, m23);
			rows[3] = Vector4(m30, m31, m32, m33);
		}

		Matrix4x4(Vector4 m0, Vector4 m1, Vector4 m2, Vector4 m3)
		{
			rows[0] = m0;
			rows[1] = m1;
			rows[2] = m2;
			rows[3] = m3;
		}

		static Matrix4x4 Identity()
		{
			return Matrix4x4(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
			);
		}

		void SetIdentity()
		{
			rows[0].x = 1;
			rows[0].y = 0;
			rows[0].z = 0;
			rows[0].w = 0;

			rows[1].x = 0;
			rows[1].y = 1;
			rows[1].z = 0;
			rows[1].w = 0;

			rows[2].x = 0;
			rows[2].y = 0;
			rows[2].z = 1;
			rows[2].w = 0;

			rows[3].x = 0;
			rows[3].y = 0;
			rows[3].z = 0;
			rows[3].w = 1;
		}

		Vector4 operator[](int index)
		{
			return rows[index];
		}

		bool operator==(Matrix4x4 other)
		{
			return rows[0] == other[0]
				&& rows[1] == other[1]
				&& rows[2] == other[2]
				&& rows[3] == other[3];
		}

		bool operator!=(Matrix4x4 other)
		{
			return !(rows[0] == other[0]
				&& rows[1] == other[1]
				&& rows[2] == other[2]
				&& rows[3] == other[3]);
		}

		// TODO: Implement Matrix4x4 arthithmetics,rx
	};
}