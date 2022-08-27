#include "epch.h"
#include "OpenGLShader.h"
#include "core/Core.h"
#include "core/Log.h"

#include <glad/glad.h>
#include <vector>

namespace Cherry
{
	OpenGLShader::OpenGLShader(std::string vertexSrc, std::string fragmentSrc)
	{
		uint32_t vertexShader = CompileVertexShader(vertexSrc);
		if (!CheckVertexShaderSuccess(vertexShader))
		{
			glDeleteShader(vertexShader);
			return;
		}

		uint32_t fragmentShader = CompileFragmentShader(fragmentSrc);
		if (!CheckFragmentShaderSuccess(fragmentShader))
		{
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			return;
		}

		LinkShaderProgram(vertexShader, fragmentShader);
		if (!CheckProgramLinkingSuccess())
		{
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			glDeleteProgram(m_ShaderProgram);
			return;
		}

		glDetachShader(m_ShaderProgram, vertexShader);
		glDetachShader(m_ShaderProgram, fragmentShader);
	}

	OpenGLShader::OpenGLShader(std::string file)
	{
		std::string vertexSrc = "";
		std::string fragmentSrc = "";

		ParseFile(file, vertexSrc, fragmentSrc);

		uint32_t vertexShader = CompileVertexShader(vertexSrc);
		if (!CheckVertexShaderSuccess(vertexShader))
		{
			glDeleteShader(vertexShader);
			return;
		}

		uint32_t fragmentShader = CompileFragmentShader(fragmentSrc);
		if (!CheckFragmentShaderSuccess(fragmentShader))
		{
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			return;
		}

		LinkShaderProgram(vertexShader, fragmentShader);
		if (!CheckProgramLinkingSuccess())
		{
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			glDeleteProgram(m_ShaderProgram);
			return;
		}

		glDetachShader(m_ShaderProgram, vertexShader);
		glDetachShader(m_ShaderProgram, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ShaderProgram);
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(m_ShaderProgram);
	}

	void OpenGLShader::Unbind()
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, const int& value)
	{
		int location = glGetUniformLocation(m_ShaderProgram, name.c_str());
		CH_ASSERT( location != -1, "invalid uniform");

		glUniform1i(location, value);
	}

	void OpenGLShader::SetInt2(const std::string& name, const Vector2i& value)
	{
		int location = glGetUniformLocation(m_ShaderProgram, name.c_str());
		CH_ASSERT( location != -1, "invalid uniform");

		glUniform1iv(location, 2, value.Data());
	}

	void OpenGLShader::SetInt3(const std::string& name, const Vector3i& value)
	{
		int location = glGetUniformLocation(m_ShaderProgram, name.c_str());
		CH_ASSERT( location != -1, "invalid uniform");

		glUniform1iv(location, 3, value.Data());
	}

	void OpenGLShader::SetInt4(const std::string& name, const Vector4i& value)
	{
		int location = glGetUniformLocation(m_ShaderProgram, name.c_str());
		CH_ASSERT( location != -1, "invalid uniform");

		glUniform1iv(location, 4, value.Data());
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* data, uint32_t size)
	{
		int location = glGetUniformLocation(m_ShaderProgram, name.c_str());
		CH_ASSERT(location != -1, "invalid uniform");

		glUniform1iv(location, size, data);
	}

	void OpenGLShader::SetFloat(const std::string& name, const float& value)
	{
		int location = glGetUniformLocation(m_ShaderProgram, name.c_str());
		CH_ASSERT( location != -1, "invalid uniform");

		glUniform1f(location, value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const Vector2f& value)
	{
		int location = glGetUniformLocation(m_ShaderProgram, name.c_str());
		CH_ASSERT( location != -1, "invalid uniform");

		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const Vector3f& value)
	{
		int location = glGetUniformLocation(m_ShaderProgram, name.c_str());
		CH_ASSERT( location != -1, "invalid uniform");

		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const Vector4f& value)
	{
		int location = glGetUniformLocation(m_ShaderProgram, name.c_str());
		CH_ASSERT( location != -1, "invalid uniform");

		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetMat3(const std::string& name, const Matrix3x3f& value)
	{
		int location = glGetUniformLocation(m_ShaderProgram, name.c_str());
		CH_ASSERT( location != -1, "invalid uniform");

		glUniformMatrix3fv(location, 1, GL_FALSE, value.ToArray());
	}

	void OpenGLShader::SetMat4(const std::string& name, const Matrix4x4f& value)
	{
		int location = glGetUniformLocation(m_ShaderProgram, name.c_str());
		CH_ASSERT( location != -1, "invalid uniform");

		glUniformMatrix4fv(location, 1, GL_FALSE, value.ToArray());
	}

	uint32_t OpenGLShader::CompileVertexShader(std::string vertexSrc)
	{
		uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const char* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		glCompileShader(vertexShader);

		return vertexShader;
	}

	bool OpenGLShader::CheckVertexShaderSuccess(uint32_t ID)
	{
		GLint success = 0;
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(ID, maxLength, &maxLength, &infoLog[0]);

			CH_ERROR(infoLog.data());
			CH_ASSERT(false, "Vertex shader compilation failed");
		}

		return success;
	}

	uint32_t OpenGLShader::CompileFragmentShader(std::string fragmentSrc)
	{
		uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		const char* source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		glCompileShader(fragmentShader);

		return fragmentShader;
	}

	bool OpenGLShader::CheckFragmentShaderSuccess(uint32_t fragmentShader)
	{
		int success;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			CH_ERROR(infoLog.data());
			CH_ASSERT(false, "Fragment shader compilation failed!");
		}

		return success;
	}

	void OpenGLShader::LinkShaderProgram(uint32_t vertex, uint32_t fragment)
	{
		m_ShaderProgram = glCreateProgram();

		glAttachShader(m_ShaderProgram, vertex);
		glAttachShader(m_ShaderProgram, fragment);

		glLinkProgram(m_ShaderProgram);
	}

	bool OpenGLShader::CheckProgramLinkingSuccess()
	{
		int isLinked = 0;
		glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			int maxLength = 0;
			glGetProgramiv(m_ShaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(m_ShaderProgram, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_ShaderProgram);

			CH_ERROR(infoLog.data());
			CH_ASSERT(false, "Shader program linking failed!");
		}

		return isLinked;
	}

	void OpenGLShader::ParseFile(std::string file, std::string& vertexSrc, std::string& fragmentSrc)
	{
		std::string line;
		std::ifstream myfile(file);

		int shaderCurrent = -1;

		CH_ASSERT(myfile.is_open(), "failed to open shader source file");
		while (getline(myfile, line))
		{
			if (line.substr(0, 7) == "@shader")
			{
				if (line.find("vertex") != std::string::npos) 
				{
					shaderCurrent = 0;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					shaderCurrent = 1;
				}
			}
			else if (shaderCurrent == 0)
			{
				vertexSrc += line + "\n";
			}
			else if (shaderCurrent == 1)
			{
				fragmentSrc += line + "\n";
			}
		}

		myfile.close();
	}
}
