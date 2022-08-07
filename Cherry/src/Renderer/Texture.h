#pragma once

#include "core/Core.h"
#include "core/Log.h"
#include "core/Pointer.h"

namespace Cherry
{
	class CHERRY_API Texture
	{
	public:

		virtual ~Texture() = default;

		virtual uint32_t GetWidth() = 0;
		virtual uint32_t GetHeight() = 0;

		virtual void Bind() = 0;
		virtual void Bind(int unit) = 0;

		static Scoped<Texture> Create(std::string path);
	};
}