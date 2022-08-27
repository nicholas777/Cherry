#pragma once

#include "core/Core.h"
#include "core/Log.h"
#include "core/Pointer.h"
#include "Math/Vector.h"

namespace Cherry
{
	class CHERRY_API Texture
	{
	public:

		virtual ~Texture() = default;

		virtual uint32_t GetWidth() = 0;
		virtual uint32_t GetHeight() = 0;

		virtual void SetData(void* data, uint32_t size) = 0;

		virtual void Bind(int unit = 0) = 0;

		static Scoped<Texture> Create(std::string path);
		static Scoped<Texture> Create(uint32_t width, uint32_t height);
	};

	struct CHERRY_API SubTexture
	{
		Texture* texture;
		Vector2f textureCoords[4];

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
