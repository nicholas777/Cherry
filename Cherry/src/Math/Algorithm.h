#pragma once

#include "core/Core.h"
#include "Vector.h"
#include "Matrix.h"

namespace Cherry
{
	class CHERRY_API Algorithm
	{
	public:
		#define det determinant

		template <typename T>
		static T determinant(Matrix2x2<T> m)
		{
			return m[0][0] * m[1][1] - m[1][0] * m[0][1];
		}

		template <typename T>
		static T determinant(Matrix3x3<T> m)
		{
			return	m[0][0] * m[1][1] * m[2][2] +
				m[1][2] * m[2][3] * m[3][1] +
				m[1][3] * m[2][1] * m[3][2] -
				m[1][3] * m[2][2] * m[3][1] -
				m[1][2] * m[2][1] * m[3][3] -
				m[1][1] * m[2][3] * m[3][2];
		}

		template <typename T>
		static T determinant(Matrix4x4<T> m)
		{
			T SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
			T SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
			T SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
			T SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
			T SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
			T SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];

			Vector4<T> DetCof(
				+(m[1][1] * SubFactor00 - m[1][2] * SubFactor01 + m[1][3] * SubFactor02),
				-(m[1][0] * SubFactor00 - m[1][2] * SubFactor03 + m[1][3] * SubFactor04),
				+(m[1][0] * SubFactor01 - m[1][1] * SubFactor03 + m[1][3] * SubFactor05),
				-(m[1][0] * SubFactor02 - m[1][1] * SubFactor04 + m[1][2] * SubFactor05));

			return
				m[0][0] * DetCof[0] + m[0][1] * DetCof[1] +
				m[0][2] * DetCof[2] + m[0][3] * DetCof[3];
		}

		template <typename T>
		static Matrix2x2<T> inverse(Matrix2x2<T> m)
		{
			T OneOverDet = 1 / det(m);

			return Matrix2x2<T>(
				m[1][1] * OneOverDet,
				-m[0][1] * OneOverDet,
				-m[1][0] * OneOverDet,
				m[0][0] * OneOverDet
				);
		}

		template <typename T>
		static Matrix3x3<T> inverse(Matrix3x3<T> m)
		{
			T OneOverDet = 1 / det(m);

			Matrix3x3<T> Inverse;
			Inverse[0][0] = +(m[1][1] * m[2][2] - m[2][1] * m[1][2]) * OneOverDet;
			Inverse[1][0] = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]) * OneOverDet;
			Inverse[2][0] = +(m[1][0] * m[2][1] - m[2][0] * m[1][1]) * OneOverDet;
			Inverse[0][1] = -(m[0][1] * m[2][2] - m[2][1] * m[0][2]) * OneOverDet;
			Inverse[1][1] = +(m[0][0] * m[2][2] - m[2][0] * m[0][2]) * OneOverDet;
			Inverse[2][1] = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]) * OneOverDet;
			Inverse[0][2] = +(m[0][1] * m[1][2] - m[1][1] * m[0][2]) * OneOverDet;
			Inverse[1][2] = -(m[0][0] * m[1][2] - m[1][0] * m[0][2]) * OneOverDet;
			Inverse[2][2] = +(m[0][0] * m[1][1] - m[1][0] * m[0][1]) * OneOverDet;
		}

		template <typename T>
		static Matrix4x4<T> inverse(Matrix4x4<T> m)
		{

			T Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
			T Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
			T Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

			T Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
			T Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
			T Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

			T Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
			T Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
			T Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

			T Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
			T Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
			T Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

			T Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
			T Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
			T Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

			T Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
			T Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
			T Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

			Vector4<T> Fac0(Coef00, Coef00, Coef02, Coef03);
			Vector4<T> Fac1(Coef04, Coef04, Coef06, Coef07);
			Vector4<T> Fac2(Coef08, Coef08, Coef10, Coef11);
			Vector4<T> Fac3(Coef12, Coef12, Coef14, Coef15);
			Vector4<T> Fac4(Coef16, Coef16, Coef18, Coef19);
			Vector4<T> Fac5(Coef20, Coef20, Coef22, Coef23);

			Vector4<T> Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
			Vector4<T> Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
			Vector4<T> Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
			Vector4<T> Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

			Vector4<T> Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
			Vector4<T> Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
			Vector4<T> Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
			Vector4<T> Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

			Vector4<T> SignA(+1, -1, +1, -1);
			Vector4<T> SignB(-1, +1, -1, +1);
			Matrix4x4<T> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

			Vector4<T> Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);

			Vector4<T> Dot0(m[0] * Row0);
			T Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

			T OneOverDeterminant = static_cast<T>(1) / Dot1;

			return Inverse * OneOverDeterminant;
		}

		// NORMALIZE

		template<typename T>
		static Vector2<T> normalize(Vector2<T> vec)
		{
			return vec / mag(vec);
		}

		template<typename T>
		static Vector3<float> normalize(Vector3<T> vec)
		{
			return Vector3<float>((float)vec.x, (float)vec.y, (float)vec.z) / mag(vec);
		}

		template<typename T>
		static Vector4<T> normalize(Vector4<T> vec)
		{
			return vec / mag(vec);
		}

		// DOT

		template<typename T>
		static T dot(Vector2<T> vec1, Vector2<T> vec2)
		{
			return
				vec1.x * vec2.x +
				vec1.y * vec2.y
		}

		template<typename T>
		static T dot(Vector3<T> vec1, Vector3<T> vec2)
		{
			return
				vec1.x * vec2.x +
				vec1.y * vec2.y +
				vec1.z * vec2.z;
		}

		template<typename T>
		static T dot(Vector4<T> vec1, Vector4<T> vec2)
		{
			return
				vec1.x * vec2.x +
				vec1.y * vec2.y +
				vec1.z * vec2.z +
				vec1.w * vec2.w
		}

		// CROSS

		template <typename T>
		static Vector3<T> cross(Vector3<T> x, Vector3<T> y)
		{
			return Vector3<T>(
				x.y * y.z - y.y * x.z,
				x.z * y.x - y.z * x.x,
				x.x * y.y - y.x * x.y
				);
		}

		// MAGNITUDE

		template <typename T>
		static float mag(Vector2<T> vec)
		{
			return sqrt(vec.x * vec.x + vec.y * vec.y);
		}

		template <typename T>
		static float mag(Vector3<T> vec)
		{
			return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
		}

		template <typename T>
		static float mag(Vector4<T> vec)
		{
			return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
		}

	};

}
