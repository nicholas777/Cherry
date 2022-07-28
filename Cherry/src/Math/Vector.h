#pragma once

#include "core/Core.h"
#include "core/Log.h"
#include <cstdint>

namespace Cherry
{
	template<typename T>
	class CHERRY_API Vector2
	{
		typedef Vector2<T> type;

	public: 
		T x, y;

		template <typename T>
		Vector2(T x, T y)
		{
			this->x = x;
			this->y = y;
		};

		Vector2()
		{
			this->x = 0;
			this->y = 0;
		}
		
		T* Data()
		{
			T* arr = new T[2];

			arr[0] = x;
			arr[1] = y;

			return arr;
		}

		float& operator[](int index)
		{
			if (index == 0) return x;
			if (index == 1) return y;

			CH_ERROR("Error in Vector::operator[]: specified index is either too large or too small");
			return 0;
		}

		bool operator==(type other)
		{
			return x == other.x && y == other.y;
		}

		bool operator!=(type other)
		{
			return !(x == other.x && y == other.y);
		}

		type operator+(type other)
		{
			return type(x + other.x, y + other.y);
		}

		template <typename T>
		type operator+(T other)
		{
			return type(x + other, y + other);
		}

		void operator+=(type other)
		{
			x += other.x;
			y += other.y;
		}

		template <typename T>
		void operator+=(T other)
		{
			x += other;
			y += other;
		}

		type operator-(type other)
		{
			return type(x - other.x, y - other.y);
		}

		template <typename T>
		type operator-(T other)
		{
			return type(x - other, y - other);
		}

		void operator-=(type other)
		{
			x -= other.x;
			y -= other.y;
		}

		template <typename T>
		void operator-=(T other)
		{
			x -= other;
			y -= other;
		}

		template <typename T>
		type operator*(T other)
		{
			return type(x * other, y * other);
		}

		type operator*(type other)
		{
			return type(x * other.x, y * other.y);
		}

		template <typename T>
		void operator*=(T other)
		{
			x *= other;
			y *= other;
		}

		void operator*=(type other)
		{
			x *= other.x;
			y *= other.x;
		}

		template <typename T>
		type operator/(T other)
		{
			return type(x / other, y / other);
		}

		type operator/(type other)
		{
			return type(x / other.x, y / other.y);
		}

		void operator/=(T other)
		{
			x /= other;
			y /= other;
		}

		void operator/=(type other)
		{
			x /= other.x;
			y /= other.y;
		}
	};

	template<typename T>
	class CHERRY_API Vector3
	{
		typedef Vector3<T> type;

	public:
		float x, y, z;

		Vector3(T x, T y, T z)
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

		template <typename T>
		Vector3(Vector2<T> vec)
		{
			x = vec.x;
			y = vec.y;
			z = 0;
		}

		T* Data()
		{
			T* arr = new T[3];

			arr[0] = x;
			arr[1] = y;
			arr[2] = z;

			return arr;
		}

		float& operator[](int index)
		{
			if (index == 0) return x;
			if (index == 1) return y;
			if (index == 2) return z;

			CH_ERROR("Error in type::operator[]: specified index is either too large or too small");
			return x;
		}

		bool operator==(type other)
		{
			return x == other.x && y == other.y && z == other.z;
		}

		bool operator!=(type other)
		{
			return !(*(this) == other);
		}

		type operator+(T other)
		{
			return type(x + other, y + other, z + other);
		}

		type operator+(type other)
		{
			return type(x + other.x, y + other.y, z + other.z);
		}

		void operator+=(T other)
		{
			x += other;
			y += other;
			z += other;
		}

		void operator+=(type other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
		}

		type operator-(T other)
		{
			return type(x - other, y - other, z - other);
		}

		type operator-(type other)
		{
			return type(x - other.x, y - other.y, z - other.z);
		}

		void operator-=(T other)
		{
			x -= other;
			y -= other;
			z -= other;
		}

		void operator-=(type other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
		}

		type operator*(T other)
		{
			return type(x * other, y * other, z * other);
		}

		type operator*(type other)
		{
			return type(x * other.x, y * other.y, z * other.z);
		}

		void operator*=(T other)
		{
			x *= other;
			y *= other;
			z *= other;
		}

		void operator*=(type other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
		}

		type operator/(T other)
		{
			return type(x / other, y / other, z / other);
		}

		type operator/(type other)
		{
			return type(x / other.x, y / other.y, z / other.z);
		}

		void operator/=(T other)
		{
			x /= other;
			y /= other;
			z /= other;
		}

		void operator/=(type other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
		}
	};

	template<typename T>
	class CHERRY_API Vector4
	{
		typedef Vector4<T> type;
	public:
		float x, y, z, w;

		Vector4(T x, T y, T z, T w)
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

		T* Data()
		{
			T* arr = new T[4];

			arr[0] = x;
			arr[1] = y;
			arr[2] = z;
			arr[3] = w;

			return arr;
		}

		float& operator[](int index)
		{
			if (index == 0) return x;
			if (index == 1) return y;
			if (index == 2) return z;
			if (index == 3) return w;

			CH_ERROR("Error in type::operator[]: specified index is either too large or too small");
			return x;
		}

		bool operator==(type other)
		{
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}

		bool operator!=(type other)
		{
			return !(*(this) == other);
		}

		type operator+(T other)
		{
			return type(x + other, y + other, z + other, w + other);
		}

		type operator+(type other)
		{
			return type(x + other.x, y + other.y, z + other.z, w + other.w);
		}

		void operator+=(T other)
		{
			x += other;
			y += other;
			z += other;
			w += other;
		}

		void operator+=(type other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
		}

		type operator-(T other)
		{
			return type(x - other, y - other, z - other, w - other);
		}

		type operator-(type other)
		{
			return type(x - other.x, y - other.y, z - other.z, w - other.w);
		}

		void operator-=(T other)
		{
			x -= other;
			y -= other;
			z -= other;
			w -= other;
		}

		void operator-=(type other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
		}

		type operator*(T other)
		{
			return type(x * other, y * other, z * other, w * other);
		}

		type operator*(type other)
		{
			return type(x * other.x, y * other.y, z * other.z, w * other.w);
		}

		void operator*=(T other)
		{
			x *= other;
			y *= other;
			z *= other;
			w *= other;
		}

		void operator*=(type other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;
		}

		type operator/(T other)
		{
			return type(x / other, y / other, z / other, w / other);
		}

		type operator/(type other)
		{
			return type(x / other.x, y / other.y, z / other.z, w / other.w);
		}

		void operator/=(T other)
		{
			x /= other;
			y /= other;
			z /= other;
			w /= other;
		}

		void operator/=(type other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;
		}
	};

	typedef Vector2<float> Vector2f;
	typedef Vector2<int> Vector2i;
	typedef Vector2<std::uint32_t> Vector2ui;
	typedef Vector2<double> Vector2d;

	typedef Vector3<float> Vector3f;
	typedef Vector3<int> Vector3i;
	typedef Vector3<std::uint32_t> Vector3ui;
	typedef Vector3<double> Vector3d;

	typedef Vector4<float> Vector4f;
	typedef Vector4<int> Vector4i;
	typedef Vector4<std::uint32_t> Vector4ui;
	typedef Vector4<double> Vector4d;
}
