#pragma once

#include "VertexArray.h"
#include "Math/Vector.h"

namespace Cherry
{
	class RenderAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL
		};
	public:

		virtual ~RenderAPI() = default;

		virtual void Init() = 0;

		virtual void SetViewport(int x, int y, int width, int height) = 0;

		virtual void SetClearColor(Vector4f color) = 0;
		virtual void Clear() = 0;

		virtual void DrawElements(VertexArray* vao, uint32_t indexCount) = 0;

		static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}