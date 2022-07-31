#pragma once

#include "core/Core.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "core/Pointer.h"
#include "Renderer/ShaderLibrary.h"

namespace Cherry
{
	class CHERRY_API Material
	{
	public:
		Material() {}
		Material(const std::string& s)
			: m_Shader(ShaderLibrary::Get(s))
		{
		}

		~Material()
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

		void AddTexture(Texture* tex);

		void Bind();

		inline Shader* GetShader() { return m_Shader.Get(); };
	private:
		Shared<Shader> m_Shader;

		std::vector<Texture*> m_Textures;
	};
}
