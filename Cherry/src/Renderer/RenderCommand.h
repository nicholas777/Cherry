#pragma once

#include "Graphics/Mesh.h"
#include "RenderAPI.h"

namespace Cherry
{
	class CHERRY_API RenderCommand
	{
	public:
		inline static void SetClearColor(Vector4f color)
		{
			s_RenderAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RenderAPI->Clear();
		}

		inline static void DrawElements(Mesh m)
		{
			s_RenderAPI->DrawElements(m.GetVAO());
		}

	private:
		static RenderAPI* s_RenderAPI;
	};
}