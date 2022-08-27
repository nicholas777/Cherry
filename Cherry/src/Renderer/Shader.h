#pragma once

#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "core/Pointer.h"
#include <string>

namespace Cherry
{
	class CHERRY_API Shader
	{
	public:

		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetInt(const std::string& name,      const int& value) = 0;
		virtual void SetInt2(const std::string& name,     const Vector2i& value) = 0;
		virtual void SetInt3(const std::string& name,     const Vector3i& value) = 0;
		virtual void SetInt4(const std::string& name,     const Vector4i& value) = 0;
		
		virtual void SetFloat(const std::string& name,    const float& value) = 0;
		virtual void SetFloat2(const std::string& name,   const Vector2f& value) = 0;
		virtual void SetFloat3(const std::string& name,   const Vector3f& value) = 0;
		virtual void SetFloat4(const std::string& name,   const Vector4f& value) = 0;

		virtual void SetMat3(const std::string& name,     const Matrix3x3f& value) = 0;
		virtual void SetMat4(const std::string& name,     const Matrix4x4f& value) = 0;

		virtual void SetIntArray(const std::string& name, int* value, uint32_t count) = 0;

		static Scoped<Shader> Create(std::string vertex, std::string fragment);
		static Scoped<Shader> Create(std::string file);
	};
}