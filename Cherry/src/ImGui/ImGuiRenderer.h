#pragma once

#include "core/Layer.h"

#include <imgui.h>

namespace Cherry
{
	class ImGuiRenderer
	{
	public:
		ImGuiRenderer() {}
		~ImGuiRenderer() {}
		
		void OnInit();
		void OnShutdown();

		void Begin();
		void End();
	};
}