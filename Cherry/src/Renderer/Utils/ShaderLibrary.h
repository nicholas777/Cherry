#pragma once

#include "../Shader.h"
#include "core/Pointer.h"

namespace Cherry
{
	class CHERRY_API ShaderLibrary
	{
	public:
		static void Set(const const std::string& name, const const std::string& shaderPath);
		static void Set(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		static void Remove(const std::string& name);

		static Scoped<Shader>& Get(const std::string& name);
		static bool Contains(const std::string& name);

	private:
		static std::unordered_map<std::string, Scoped<Shader>> m_Shaders;
	};
}