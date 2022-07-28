#pragma once

#include "core/Core.h"
#include "Renderer/Shader.h"

namespace Cherry
{
	class CHERRY_API Material
	{
	public:
		Material() {}
		Material(Shader* s)
			: m_Shader(s)
		{
		}

		void Set(std::string name, float value);
		void Set(std::string name, Vector2f value);
		void Set(std::string name, Vector3f value);
		void Set(std::string name, Vector4f value);

		void Set(std::string name, int value);
		void Set(std::string name, Vector2i value);
		void Set(std::string name, Vector3i value);
		void Set(std::string name, Vector4i value);

		void Set(std::string name, Matrix3x3f value);
		void Set(std::string name, Matrix4x4f value);

		void Bind();

		inline Shader* GetShader() { return m_Shader; };
	private:
		Shader* m_Shader;
	};
}