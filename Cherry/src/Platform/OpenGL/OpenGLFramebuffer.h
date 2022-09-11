#pragma once

#include "Renderer/Framebuffer.h"

namespace Cherry
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer();
		~OpenGLFramebuffer();

		virtual void Bind() override;
	};
}