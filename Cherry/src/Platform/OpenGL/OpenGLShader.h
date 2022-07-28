#pragma once

#include <string>

#include "Renderer/Shader.h"

namespace Cherry
{
	class CHERRY_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader(std::string vertexSrc, std::string fragmentSrc);
		OpenGLShader(std::string file);
		~OpenGLShader();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetInt2(const std::string& name, Vector2i value) override;
		virtual void SetInt3(const std::string& name, Vector3i value) override;
		virtual void SetInt4(const std::string& name, Vector4i value) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat2(const std::string& name, Vector2f value) override;
		virtual void SetFloat3(const std::string& name, Vector3f value) override;
		virtual void SetFloat4(const std::string& name, Vector4f value) override;
		virtual void SetMat3(const std::string& name, Matrix3x3f value) override;
		virtual void SetMat4(const std::string& name, Matrix4x4f value) override;

	private:
		unsigned int m_ShaderProgram;

		uint32_t CompileVertexShader(std::string vertexSrc);
		bool CheckVertexShaderSuccess(uint32_t ID);

		uint32_t CompileFragmentShader(std::string vertexSrc);
		bool CheckFragmentShaderSuccess(uint32_t ID);

		void LinkShaderProgram(uint32_t vertex, uint32_t fragment);
		bool CheckProgramLinkingSuccess();

		void ParseFile(std::string file, std::string& vertexSrc, std::string& fragmentSrc);
	};
}