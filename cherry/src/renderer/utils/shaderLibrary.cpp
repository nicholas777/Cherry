#include "shaderLibrary.h"

#include "epch.h"

namespace Cherry {
    std::unordered_map<std::string, Scoped<Shader>> ShaderLibrary::m_Shaders =
        std::unordered_map<std::string, Scoped<Shader>>();

    void ShaderLibrary::Set(const std::string& name, const std::string& shaderPath) {
        m_Shaders[name] = Shader::Create(shaderPath);
    }

    void ShaderLibrary::Set(const std::string& name, const std::string& vertexSrc,
                            const std::string& fragmentSrc) {
        m_Shaders[name] = Shader::Create(vertexSrc, fragmentSrc);
    }

    void ShaderLibrary::Remove(const std::string& name) {
        CH_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Shader not found");
        m_Shaders.erase(name);
    }

    Scoped<Shader>& ShaderLibrary::Get(const std::string& name) {
        CH_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Shader not found");
        return m_Shaders[name];
    }

    bool ShaderLibrary::Contains(const std::string& name) {
        return m_Shaders.find(name) != m_Shaders.end();
    }
}
