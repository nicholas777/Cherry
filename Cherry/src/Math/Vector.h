#pragma once

#include "core/Core.h"
#include "core/Log.h"
#include <cstdint>

namespace Cherry
{
	template<typename T>
	class Vector3;

	template<typename T>
	class Vector4;

	template<typename T>
	class Vector2
	{
		typedef Vector2<T> type;

	public: 
		T x, y;

		Vector2(const T& x, const T& y)
		{
			this->x = x;
			this->y = y;
		};

		Vector2(T vec[2])
		{
			x = vec[0];
			y = vec[1];
		}

		Vector2()
		{
			this->x = 0;
			this->y = 0;
		}

		Vector2(const T& value)
		{
			x = value;
			y = value;
		}

 		Vector2(const Vector3<T>& value)
		{
			x = value.x;
			y = value.y;
		}

		Vector2(const Vector4<T>& value)
		{
			x = value.x;
			y = value.y;
		}
		
		T* Data() const
		{
			T* arr = new T[2];

			arr[0] = x;
			arr[1] = y;

			return arr;
		}

		const float& operator[](int index) const
		{
			CH_ASSERT(!(index > 1 || index < 0), "specified index is either too large or too small");
			
			if (index == 0) return x;
			else return y;

		}

		bool operator==(const type& other) const
		{
			return x == other.x && y == other.y;
		}

		bool operator!=(const type& other) const
		{
			return !(x == other.x && y == other.y);
		}

		type operator-() const
		{
			return type(-x, -y);
		}

		type operator+(const type& other) const
		{
			return type(x + other.x, y + other.y);
		}

		type operator+(const T& other) const
		{
			return type(x + other, y + other);
		}

		void operator+=(const type& other)
		{
			x += other.x;
			y += other.y;
		}

		void operator+=(const T& other)
		{
			x += other;
			y += other;
		}

		type operator-(const type& other) const
		{
			return type(x - other.x, y - other.y);
		}

		type operator-(const T& other) const
		{
			return type(x - other, y - other);
		}

		void operator-=(const type& other)
		{
			x -= other.x;
			y -= other.y;
		}

		void operator-=(const T& other)
		{
			x -= other;
			y -= other;
		}

		type operator*(const T& other) const
		{
			return type(x * other, y * other);
		}

		type operator*(const type& other) const
		{
			return type(x * other.x, y * other.y);
		}

		void operator*=(const T& other)
		{
			x *= other;
			y *= other;
		}

		void operator*=(const type& other)
		{
			x *= other.x;
			y *= other.x;
		}

		type operator/(const T& other) const
		{
			return type(x / other, y / other);
		}

		type operator/(const type& other) const
		{
			return type(x / other.x, y / other.y);
		}

		void operator/=(const T& other)
		{
			x /= other;
			y /= other;
		}

		void operator/=(const type& other)
		{
			x /= other.x;
			y /= other.y;
		}
	};

	template<typename T>
	class Vector3
	{
		typedef Vector3<T> type;

	public:
		T x, y, z;

		constexpr Vector3(const T& x, const T& y, const T& z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vector3(const Vector2<T>& vec, const T& z)
		{
			this->x = vec.x;
			this->y = vec.y;
			this->z = z;
		}

		Vector3(const T& x, const Vector2<T>& vec)
		{
			this->x = x;
			this->y = vec.x;
			this->z = vec.y;
		}

		Vector3(T vec[3])
		{
			x = vec[0];
			y = vec[1];
			z = vec[2];
		}

		Vector3()
		{
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}

		Vector3(const T& value)
		{
			x = value;
			y = value;
			z = value;
		}

		Vector3(const Vector4<T>& value)
		{
			x = value.x;
			y = value.y;
			z = value.z;
		}

		T* Data() const
		{
			T* arr = new T[3];

			arr[0] = x;
			arr[1] = y;
			arr[2] = z;

			return arr;
		}

		const float& operator[](int index) const
		{
			CH_ASSERT(!(index < 0 || index > 2), "specified index is either too large or too small");
			
			if (index == 0) return x;
			if (index == 1) return y;
			else return z;
		}

		bool operator==(const type& other) const
		{
			return x == other.x && y == other.y && z == other.z;
		}

		bool operator!=(const type& other) const
		{
			return !(*(const T&his) == other);
		}

		type operator-() const
		{
			return type(-x, -y, -z);
		}

		type operator+(const T& other) const
		{
			return type(x + other, y + other, z + other);
		}

		type operator+(const type& other) const
		{
			return type(x + other.x, y + other.y, z + other.z);
		}

		void operator+=(const T& other)
		{
			x += other;
			y += other;
			z += other;
		}

		void operator+=(const type& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
		}

		type operator-(const T& other) const
		{
			return type(x - other, y - other, z - other);
		}

		type operator-(const type& other) const
		{
			return type(x - other.x, y - other.y, z - other.z);
		}

		void operator-=(const T& other)
		{
			x -= other;
			y -= other;
			z -= other;
		}

		void operator-=(const type& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
		}

		type operator*(const T& other) const
		{
			return type(x * other, y * other, z * other);
		}

		type operator*(const type& other) const
		{
			return type(x * other.x, y * other.y, z * other.z);
		}

		void operator*=(const T& other)
		{
			x *= other;
			y *= other;
			z *= other;
		}

		void operator*=(const type& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
		}

		type operator/(const T& other) const
		{
			return type(x / other, y / other, z / other);
		}

		type operator/(const type& other) const
		{
			return type(x / other.x, y / other.y, z / other.z);
		}

		void operator/=(const T& other)
		{
			x /= other;
			y /= other;
			z /= other;
		}

		void operator/=(const type& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
		}
	};

	template<typename T>
	class Vector4
	{
		typedef Vector4<T> type;
	public:
		T x, y, z, w;

		Vector4(const T& x, const T& y, const T& z, const T& w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		Vector4(T vec[4])
		{
			x = vec[0];
			y = vec[1];
			z = vec[2];
			w = vec[3];
		}

		Vector4()
		{
			this->x = 0;
			this->y = 0;
			this->z = 0;
			this->w = 0;
		}

		Vector4(const Vector2<T>& vec, const T& z, const T& w)
		{
			this->x = vec.x;
			this->y = vec.y;
			this->z = z;
			this->w = w;
		}

		Vector4(const Vector3<T>& vec, const T& w)
		{
			this->x = vec.x;
			this->y = vec.y;
			this->z = vec.z;
			this->w = w;
		}

		Vector4(const T& x, const Vector2<T>& vec, const T& w)
		{
			this->x = x;
			this->y = vec.x;
			this->z = vec.y;
			this->w = w;
		}
		
		Vector4(const T& x, const Vector3<T>& vec)
		{
			this->x = x;
			this->y = vec.x;
			this->z = vec.y;
			this->w = vec.z;
		}

		Vector4(const T& x, const T& y, const Vector2<T>& vec)
		{
			this->x = x;
			this->y = y;
			this->z = vec.x;
			this->w = vec.y;
		}

		Vector4(const Vector2<T>& vec1, const Vector2<T>& vec2)
		{
			x = vec1.x;
			y = vec1.y;
			z = vec2.x;
			w = vec2.y;
		}

		Vector4(const T& value)
		{
			x = value;
			y = value;
			z = value;
			w = value;
		}

		T* Data() const
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
			CH_ASSERT(!(index < 0 || index > 3), "specified index is either too large or too small");

			if (index == 0) return x;
			if (index == 1) return y;
			if (index == 2) return z;
			else return w;
		}

		const float& operator[](int index) const
		{
			CH_ASSERT(!(index < 0 || index > 3), "specified index is either too large or too small");
			
			if (index == 0) return x;
			if (index == 1) return y;
			if (index == 2) return z;
			else return w;
		}

		bool operator==(const type& other) const
		{
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}

		bool operator!=(const type& other) const
		{
			return !(*(const T&his) == other);
		}

		type operator-() const 
		{
			return type(-x, -y, -z, -w);
		}

		type operator+(const T& other) const
		{
			return type(x + other, y + other, z + other, w + other);
		}

		type operator+(const type& other) const
		{
			return type(x + other.x, y + other.y, z + other.z, w + other.w);
		}

		void operator+=(const T& other)
		{
			x += other;
			y += other;
			z += other;
			w += other;
		}

		void operator+=(const type& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
		}

		type operator-(const T& other) const
		{
			return type(x - other, y - other, z - other, w - other);
		}

		type operator-(const type& other) const
		{
			return type(x - other.x, y - other.y, z - other.z, w - other.w);
		}

		void operator-=(const T& other)
		{
			x -= other;
			y -= other;
			z -= other;
			w -= other;
		}

		void operator-=(const type& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
		}

		type operator*(const T& other) const
		{
			return type(x * other, y * other, z * other, w * other);
		}

		type operator*(const type& other) const
		{
			return type(x * other.x, y * other.y, z * other.z, w * other.w);
		}

		void operator*=(const T& other)
		{
			x *= other;
			y *= other;
			z *= other;
			w *= other;
		}

		void operator*=(const type& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;
		}

		type operator/(const T& other) const
		{
			return type(x / other, y / other, z / other, w / other);
		}

		type operator/(const type& other) const
		{
			return type(x / other.x, y / other.y, z / other.z, w / other.w);
		}

		void operator/=(const T& other)
		{
			x /= other;
			y /= other;
			z /= other;
			w /= other;
		}

		void operator/=(const type& other)
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
