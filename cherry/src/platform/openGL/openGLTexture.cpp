#include "epch.h"

#include "core/log.h"
#include "debug/profiler.h"
#include "openGLTexture.h"

#include "stb_image.h"

namespace Cherry
{
    // TODO: Immutable texture storage
    static GLenum ToGLFormat(TextureWrap wrap)
    {
        switch (wrap)
        {
        case TextureWrap::Repeat:
            return GL_REPEAT;
        case TextureWrap::MirroredRepeat:
            return GL_MIRRORED_REPEAT;
        case TextureWrap::ClampToBorder:
            return GL_CLAMP_TO_BORDER;
        case TextureWrap::ClampToEdge:
            return GL_CLAMP_TO_EDGE;
        default:
            CH_ASSERT(false, "Unknown Texture wrap");
            return 0;
        }
    }

    static GLenum ToGLFormat(TextureFilter wrap)
    {
        switch (wrap)
        {
        case TextureFilter::Linear:
            return GL_LINEAR;
        case TextureFilter::Nearest:
            return GL_NEAREST;
        default:
            CH_ASSERT(false, "Unknown Texture filter");
            return 0;
        }
    }

    static GLenum ToGLFormat(TextureFormat wrap)
    {
        switch (wrap)
        {
        case TextureFormat::RGBA:
            return GL_RGBA;
        case TextureFormat::RGB:
            return GL_RGB;
        case TextureFormat::Luminance:
            return GL_RED;
        case TextureFormat::LuminanceWithAlpha:
            return GL_RG;
        case TextureFormat::Depth24Stencil8:
            return GL_DEPTH_STENCIL;
        default:
            CH_ASSERT(false, "Unknown Texture format");
            return 0;
        }
    }


    OpenGLTexture::OpenGLTexture(std::string path)
    {
        CH_PROFILE_FUNC();
        int width, height, channels;

        stbi_set_flip_vertically_on_load(true);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        CH_ASSERT(data, "failed to load texture image");

        m_Width = width;
        m_Height = height;
        
        if (channels == 3)
        {
            m_Format = GL_RGB;
            m_InternalFormat = GL_RGB8;
        }
        else if (channels == 4)
        {
            m_Format = GL_RGBA;
            m_InternalFormat = GL_RGBA8;
        }

        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);

        glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, width, height, 0, m_Format, GL_UNSIGNED_BYTE, data);

        glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        stbi_image_free(data);
    }

    OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height)
        :m_Width(width), m_Height(height), m_Format(GL_RGBA), m_InternalFormat(GL_RGBA8)
    {
        CH_PROFILE_FUNC();

        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);

        glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture::OpenGLTexture(std::string path, TextureParams params)
    {
        CH_PROFILE_FUNC();

        int width, height, channels;

        stbi_set_flip_vertically_on_load(true);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        CH_ASSERT(data, "failed to load texture image");

        if (params.format == TextureFormat::Auto)
        {
            switch (channels)
            {
                case 1:
                    m_Format = GL_RED;
                    break;
                case 2:
                    m_Format = GL_RG;
                    break;
                case 3:
                    m_Format = GL_RGB;
                    break;
                case 4:
                    m_Format = GL_RGBA;
                    break;
                default:
                    CH_ASSERT(false, "Unknown texture format");
                    break;
            }
        }
        else
        {
            m_Format = ToGLFormat(params.format);
        }

        m_Width = width;
        m_Height = height;

        if (params.format == TextureFormat::RGBA)
            m_InternalFormat = GL_RGBA8;
        else if (params.format == TextureFormat::RGB)
            m_InternalFormat = GL_RGB8;
        else
            m_InternalFormat = m_Format;

        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        
        glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, width, height, 0, m_Format, GL_UNSIGNED_BYTE, data);

        // TODO: Random access violation sometimes happens here:
        // Exception thrown at 0x00007FFD3214C75B (ig9icd64.dll)
        // in Blossom.exe: 0xC0000005: Access violation reading location 
        glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, ToGLFormat(params.minFilter));
        glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, ToGLFormat(params.magFilter));
        
        if (params.wrap != TextureWrap::None)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ToGLFormat(params.wrap));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ToGLFormat(params.wrap));
        }

        stbi_image_free(data);
    }

    OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height, TextureParams params)
        : m_Width(width), m_Height(height)
    {
        CH_PROFILE_FUNC();
        if (params.format == TextureFormat::Auto)
        {
            CH_ASSERT(false, "Auto texture format not allowed in this function");
        }
        else
        {
            m_Format = ToGLFormat(params.format);
        }

        if (params.format == TextureFormat::RGBA)
            m_InternalFormat = GL_RGBA8;
        else if (params.format == TextureFormat::RGB)
            m_InternalFormat = GL_RGB8;
        else if (params.format == TextureFormat::Depth24Stencil8)
            m_InternalFormat = GL_DEPTH24_STENCIL8;
        else
            m_InternalFormat = m_Format;

        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);

        glTexImage2D(GL_TEXTURE_2D, 0, 
            m_InternalFormat, 
            width, height, 0,
            m_Format, 
            m_Format == GL_DEPTH_STENCIL ? GL_UNSIGNED_INT_24_8 : GL_UNSIGNED_BYTE, nullptr);

        glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, ToGLFormat(params.minFilter));
        glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, ToGLFormat(params.magFilter));
        
        if (params.wrap != TextureWrap::None)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ToGLFormat(params.wrap));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ToGLFormat(params.wrap));
        }
    }

    OpenGLTexture::~OpenGLTexture()
    {
        glDeleteTextures(1, &m_TextureID);
    }

    void OpenGLTexture::ResetParams(TextureParams params)
    {
        CH_PROFILE_FUNC();
        Bind();

        glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, ToGLFormat(params.minFilter));
        glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, ToGLFormat(params.magFilter));

        if (params.wrap != TextureWrap::None)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ToGLFormat(params.wrap));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ToGLFormat(params.wrap));
        }
    }

    void OpenGLTexture::SetData(void* data)
    {
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_Format, m_Format == GL_DEPTH_STENCIL ? GL_UNSIGNED_INT_24_8 : GL_UNSIGNED_BYTE, data);
    }

    void OpenGLTexture::Bind(int unit)
    {
        glBindTextureUnit(unit, m_TextureID);
    }

}
