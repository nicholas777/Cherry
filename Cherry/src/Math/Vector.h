#pragma once

#include "core/Core.h"

namespace Cherry
{

	class CHERRY_API Vector2
	{
	public:
		float x, y;

		Vector2(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		Vector2()
		{
			this->x = 0;
			this->y = 0;
		}

		float operator[](int index)
		{
			if (index == 0) return x;
			if (index == 1) return y;

			CH_ERROR("Error in Vector2::operator[]: specified index is either too large or too small");
			return 0;
		}

		bool operator==(Vector2 other)
		{
			return x == other.x && y == other.y;
		}

		bool operator!=(Vector2 other)
		{
			return !(*(this) == other);
		}

		Vector2 operator+(Vector2 other)
		{
			return Vector2(x + other.x, y + other.y);
		}

		Vector2 operator+(int other)
		{
			return Vector2(x + other, y + other);
		}

		Vector2 operator+(float other)
		{
			return Vector2(x + other, y + other);
		}

		Vector2 operator+(double other)
		{
			return Vector2(x + other, y + other);
		}

		void operator+=(Vector2 other)
		{
			x += other.x;
			y += other.y;
		}

		void operator+=(int other)
		{
			x += other;
			y += other;
		}

		void operator+=(float other)
		{
			x += other;
			y += other;
		}

		void operator+=(double other)
		{
			x += other;
			y += other;
		}

		Vector2 operator-(Vector2 other)
		{
			return Vector2(x - other.x, y - other.y);
		}

		Vector2 operator-(int other)
		{
			return Vector2(x - other, y - other);
		}

		Vector2 operator-(float other)
		{
			return Vector2(x - other, y - other);
		}

		Vector2 operator-(double other)
		{
			return Vector2(x - other, y - other);
		}

		void operator-=(Vector2 other)
		{
			x -= other.x;
			y -= other.y;
		}

		void operator-=(int other)
		{
			x -= other;
			y -= other;
		}

		void operator-=(float other)
		{
			x -= other;
			y -= other;
		}

		void operator-=(double other)
		{
			x -= other;
			y -= other;
		}

		Vector2 operator*(int other)
		{
			return Vector2(x * other, y * other);
		}

		Vector2 operator*(float other)
		{
			return Vector2(x * other, y * other);
		}

		Vector2 operator*(double other)
		{
			return Vector2(x * other, y * other);
		}

		Vector2 operator*(Vector2 other)
		{
			return Vector2(x * other.x, y * other.y);
		}

		void operator*=(int other)
		{
			x *= other;
			y *= other;
		}

		void operator*=(float other)
		{
			x *= other;
			y *= other;
		}

		void operator*=(double other)
		{
			x *= other;
			y *= other;
		}

		void operator*=(Vector2 other)
		{
			x *= other.x;
			y *= other.x;
		}

		Vector2 operator/(int other)
		{
			return Vector2(x / other, y / other);
		}

		Vector2 operator/(float other)
		{
			return Vector2(x / other, y / other);
		}

		Vector2 operator/(double other)
		{
			return Vector2(x / other, y / other);
		}

		Vector2 operator/(Vector2 other)
		{
			return Vector2(x / other.x, y / other.y);
		}

		void operator/=(int other)
		{
			x /= other;
			y /= other;
		}

		void operator/=(float other)
		{
			x /= other;
			y /= other;
		}

		void operator/=(double other)
		{
			x /= other;
			y /= other;
		}

		void operator/=(Vector2 other)
		{
			x /= other.x;
			y /= other.y;
		}
	};

	class CHERRY_API Vector3
	{
	public:
		float x, y, z;

		Vector3(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vector3()
		{
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}

		float operator[](int index)
		{
			if (index == 0) return x;
			if (index == 1) return y;
			if (index == 2) return z;

			CH_ERROR("Error in Vector3::operator[]: specified index is either too large or too small");
			return 0;
		}

		bool operator==(Vector3 other)
		{
			return x == other.x && y == other.y && z == other.z;
		}

		bool operator!=(Vector3 other)
		{
			return !(*(this) == other);
		}

		Vector3 operator+(int other)
		{
			return Vector3(x + other, y + other, z + other);
		}

		Vector3 operator+(float other)
		{
			return Vector3(x + other, y + other, z + other);
		}

		Vector3 operator+(double other)
		{
			return Vector3(x + other, y + other, z + other);
		}

		Vector3 operator+(Vector3 other)
		{
			return Vector3(x + other.x, y + other.y, z + other.z);
		}

		void operator+=(int other)
		{
			x += other;
			y += other;
			z += other;
		}

		void operator+=(float other)
		{
			x += other;
			y += other;
			z += other;
		}

		void operator+=(double other)
		{
			x += other;
			y += other;
			z += other;
		}

		void operator+=(Vector3 other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
		}

		Vector3 operator-(int other)
		{
			return Vector3(x - other, y - other, z - other);
		}

		Vector3 operator-(float other)
		{
			return Vector3(x - other, y - other, z - other);
		}

		Vector3 operator-(double other)
		{
			return Vector3(x - other, y - other, z - other);
		}

		Vector3 operator-(Vector3 other)
		{
			return Vector3(x - other.x, y - other.y, z - other.z);
		}

		void operator-=(int other)
		{
			x -= other;
			y -= other;
			z -= other;
		}

		void operator-=(float other)
		{
			x -= other;
			y -= other;
			z -= other;
		}

		void operator-=(double other)
		{
			x -= other;
			y -= other;
			z -= other;
		}

		void operator-=(Vector3 other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
		}

		Vector3 operator*(int other)
		{
			return Vector3(x * other, y * other, z * other);
		}

		Vector3 operator*(float other)
		{
			return Vector3(x * other, y * other, z * other);
		}

		Vector3 operator*(double other)
		{
			return Vector3(x * other, y * other, z * other);
		}

		Vector3 operator*(Vector3 other)
		{
			return Vector3(x * other.x, y * other.y, z * other.z);
		}

		void operator*=(int other)
		{
			x -= other;
			y -= other;
			z -= other;
		}

		void operator*=(float other)
		{
			x *= other;
			y *= other;
			z *= other;
		}

		void operator*=(double other)
		{
			x *= other;
			y *= other;
			z *= other;
		}

		void operator*=(Vector3 other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
		}

		Vector3 operator/(int other)
		{
			return Vector3(x / other, y / other, z / other);
		}

		Vector3 operator/(float other)
		{
			return Vector3(x / other, y / other, z / other);
		}

		Vector3 operator/(double other)
		{
			return Vector3(x / other, y / other, z / other);
		}

		Vector3 operator/(Vector3 other)
		{
			return Vector3(x / other.x, y / other.y, z / other.z);
		}

		void operator/=(int other)
		{
			x /= other;
			y /= other;
			z /= other;
		}

		void operator/=(float other)
		{
			x /= other;
			y /= other;
			z /= other;
		}

		void operator/=(double other)
		{
			x /= other;
			y /= other;
			z /= other;
		}

		void operator/=(Vector3 other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
		}
	};

	class CHERRY_API Vector4
	{
	public:
		float x, y, z, w;

		Vector4(float x, float y, float z, float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		Vector4()
		{
			this->x = 0;
			this->y = 0;
			this->z = 0;
			this->w = 0;
		}

		float operator[](int index)
		{
			if (index == 0) return x;
			if (index == 1) return y;
			if (index == 2) return z;
			if (index == 3) return w;

			CH_ERROR("Error in Vector4::operator[]: specified index is either too large or too small");
			return 0;
		}

		bool operator==(Vector4 other)
		{
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}

		bool operator!=(Vector4 other)
		{
			return !(*(this) == other);
		}

		Vector4 operator+(int other)
		{
			return Vector4(x + other, y + other, z + other, w + other);
		}

		Vector4 operator+(float other)
		{
			return Vector4(x + other, y + other, z + other, w + other);
		}

		Vector4 operator+(double other)
		{
			return Vector4(x + other, y + other, z + other, w + other);
		}

		Vector4 operator+(Vector4 other)
		{
			return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
		}

		void operator+=(int other)
		{
			x += other;
			y += other;
			z += other;
			w += other;
		}

		void operator+=(float other)
		{
			x += other;
			y += other;
			z += other;
			w += other;
		}

		void operator+=(double other)
		{
			x += other;
			y += other;
			z += other;
			w += other;
		}

		void operator+=(Vector4 other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
		}

		Vector4 operator-(int other)
		{
			return Vector4(x - other, y - other, z - other, w - other);
		}

		Vector4 operator-(float other)
		{
			return Vector4(x - other, y - other, z - other, w - other);
		}

		Vector4 operator-(double other)
		{
			return Vector4(x - other, y - other, z - other, w - other);
		}

		Vector4 operator-(Vector4 other)
		{
			return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
		}

		void operator-=(int other)
		{
			x -= other;
			y -= other;
			z -= other;
			w -= other;
		}

		void operator-=(float other)
		{
			x -= other;
			y -= other;
			z -= other;
			w -= other;
		}

		void operator-=(double other)
		{
			x -= other;
			y -= other;
			z -= other;
			w -= other;
		}

		void operator-=(Vector4 other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
		}

		Vector4 operator*(int other)
		{
			return Vector4(x * other, y * other, z * other, w * other);
		}

		Vector4 operator*(float other)
		{
			return Vector4(x * other, y * other, z * other, w * other);
		}

		Vector4 operator*(double other)
		{
			return Vector4(x * other, y * other, z * other, w * other);
		}

		Vector4 operator*(Vector4 other)
		{
			return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
		}

		void operator*=(int other)
		{
			x *= other;
			y *= other;
			z *= other;
			w *= other;
		}

		void operator*=(float other)
		{
			x *= other;
			y *= other;
			z *= other;
			w *= other;
		}

		void operator*=(double other)
		{
			x *= other;
			y *= other;
			z *= other;
			w *= other;
		}

		void operator*=(Vector4 other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;
		}

		Vector4 operator/(int other)
		{
			return Vector4(x / other, y / other, z / other, w / other);
		}

		Vector4 operator/(float other)
		{
			return Vector4(x / other, y / other, z / other, w / other);
		}

		Vector4 operator/(double other)
		{
			return Vector4(x / other, y / other, z / other, w / other);
		}

		Vector4 operator/(Vector4 other)
		{
			return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
		}

		void operator/=(int other)
		{
			x /= other;
			y /= other;
			z /= other;
			w /= other;
		}

		void operator/=(float other)
		{
			x /= other;
			y /= other;
			z /= other;
			w /= other;
		}

		void operator/=(double other)
		{
			x /= other;
			y /= other;
			z /= other;
			w /= other;
		}

		void operator/=(Vector4 other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;
		}
	};
}
