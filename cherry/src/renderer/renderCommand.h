#pragma once

#include "renderAPI.h"
#include "vertexArray.h"
#include "math/vector.h"

namespace Cherry
{
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			s_RenderAPI->Init();
		}

		inline static void SetViewport(int x, int y, int width, int height)
		{
			s_RenderAPI->SetViewport(x, y, width, height);
		};

		inline static void SetClearColor(Vector4f color)
		{
			s_RenderAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RenderAPI->Clear();
		}

		inline static void DrawElements(VertexArray* vao, uint32_t indexCount = -1)
		{
			s_RenderAPI->DrawElements(vao, indexCount);
		}

	private:
		static RenderAPI* s_RenderAPI;
	};
}
