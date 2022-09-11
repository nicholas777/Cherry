#pragma once

#include "core/Core.h"
#include "core/Log.h"
#include "core/Pointer.h"
#include "Math/Vector.h"

namespace Cherry
{
	enum class TextureWrap
	{
		Unknown = 0,
		Repeat, MirroredRepeat, ClampToEdge, ClampToBorder
	};

	enum class TextureFilter
	{
		Unknown = 0,
		Nearest, Linear
	};

	enum class TextureFormat
	{
		Unknown = 0,
		RGBA, RGB,
		Luminance, LuminanceWithAlpha,
		Auto
	};

	// TODO: Mipmapping
	struct TextureParams
	{
		TextureWrap wrap = TextureWrap::Repeat;
		Vector4f borderColor;

		TextureFilter minFilter = TextureFilter::Nearest;
		TextureFilter magFilter = TextureFilter::Linear;


		TextureFormat format = TextureFormat::RGBA;

		TextureParams() {}

		TextureParams(TextureWrap twrap, TextureFilter filterMin, TextureFilter filterMag, TextureFormat tformat)
			: wrap(twrap), minFilter(filterMin), magFilter(filterMag), format(tformat)
		{
		}
	};

	class Texture
	{
	public:

		virtual ~Texture() = default;

		virtual uint32_t GetWidth() = 0;
		virtual uint32_t GetHeight() = 0;

		virtual void SetData(void* data) = 0;

		virtual void Bind(int unit = 0) = 0;

		static Scoped<Texture> Create(std::string path);
		static Scoped<Texture> Create(uint32_t width, uint32_t height);

		static Scoped<Texture> Create(std::string path, TextureParams params);
		static Scoped<Texture> Create(uint32_t width, uint32_t height, TextureParams params);
	};

	struct SubTexture
	{
		Texture* texture;
		Vector2f textureCoords[4];

		SubTexture()
			: texture(nullptr) {};

		SubTexture(Texture* tex, const Vector2f& vec1, const Vector2f& vec2, const Vector2f& vec3, const Vector2f& vec4)
		{
			textureCoords[0] = vec1;
			textureCoords[1] = vec2;
			textureCoords[2] = vec3;
			textureCoords[3] = vec4;

			texture = tex;
		}
	};
}
