#include "epch.h"
#include "Material.h"

namespace Cherry
{
	void Material::Set(std::string name, float value)
	{
		m_Shader->SetFloat(name, value);
	}

	void Material::Set(std::string name, Vector2f value)
	{
		m_Shader->SetFloat2(name, value);
	}

	void Material::Set(std::string name, Vector3f value)
	{
		m_Shader->SetFloat3(name, value);
	}

	void Material::Set(std::string name, Vector4f value)
	{
		m_Shader->SetFloat4(name, value);
	}



	void Material::Set(std::string name, int value)
	{
		m_Shader->SetInt(name, value);
	}

	void Material::Set(std::string name, Vector2i value)
	{
		m_Shader->SetInt2(name, value);
	}

	void Material::Set(std::string name, Vector3i value)
	{
		m_Shader->SetInt3(name, value);
	}

	void Material::Set(std::string name, Vector4i value)
	{
		m_Shader->SetInt4(name, value);
	}



	void Material::Set(std::string name, Matrix3x3f value)
	{
		m_Shader->SetMat3(name, value);
	}

	void Material::Set(std::string name, Matrix4x4f value)
	{
		m_Shader->SetMat4(name, value);
	}
}
