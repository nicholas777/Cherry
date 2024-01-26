#pragma once

#include "core/pointer.h"
#include "math/vector.h"

namespace Cherry {
    enum class TextureWrap { None = 0, Repeat, MirroredRepeat, ClampToEdge, ClampToBorder };

    enum class TextureFilter { Unknown = 0, Nearest, Linear };

    enum class TextureFormat {
        Unknown = 0,
        RGBA,
        RGB,
        Luminance,
        LuminanceWithAlpha,
        Depth24Stencil8,
        Auto
    };

    // TODO: Mipmapping
    struct TextureParams {
        TextureWrap wrap = TextureWrap::Repeat;
        Vector4f borderColor;

        TextureFilter minFilter = TextureFilter::Nearest;
        TextureFilter magFilter = TextureFilter::Linear;

        TextureFormat format = TextureFormat::RGBA;

        TextureParams() {}

        TextureParams(TextureWrap twrap, TextureFilter filterMin, TextureFilter filterMag,
                      TextureFormat tformat)
            : wrap(twrap), minFilter(filterMin), magFilter(filterMag), format(tformat) {}
    };

    class Texture
    {
    public:

        virtual ~Texture() = default;

        virtual uint32_t GetWidth() = 0;
        virtual uint32_t GetHeight() = 0;

        virtual void SetData(void* data) = 0;
        virtual void ResetParams(TextureParams params) = 0;
        virtual uint32_t GetTextureID() = 0;

        virtual void Bind(int unit = 0) = 0;

        static Shared<Texture> Create(std::string path);
        static Shared<Texture> Create(uint32_t width, uint32_t height);

        static Shared<Texture> Create(std::string path, TextureParams params);
        static Shared<Texture> Create(uint32_t width, uint32_t height, TextureParams params);
    };

    struct SubTexture {
        Shared<Texture> texture;
        Vector2f textureCoords[4];

        SubTexture(): texture(nullptr){};

        SubTexture(Shared<Texture> tex, const Vector2f& vec1, const Vector2f& vec2,
                   const Vector2f& vec3, const Vector2f& vec4) {
            textureCoords[0] = vec1;
            textureCoords[1] = vec2;
            textureCoords[2] = vec3;
            textureCoords[3] = vec4;

            texture = tex;
        }

        SubTexture(Shared<Texture> tex, const Vector2f& bottomLeft = Vector2f(0.0f, 0.0f),
                   const Vector2f& topRight = Vector2f(1.0, 1.0)) {
            textureCoords[0] = bottomLeft;
            textureCoords[1] = Vector2f(topRight.x, bottomLeft.y);
            textureCoords[2] = topRight;
            textureCoords[3] = Vector2f(bottomLeft.x, topRight.y);

            texture = tex;
        }
    };
}
