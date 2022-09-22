#pragma once

#include <Cherry.h>

namespace Cherry
{
	class PropertiesPanel
	{
	public:
		PropertiesPanel();
		
		void SetEntity(const Entity& e);
		void SetAsset(Asset* a);
		void OnUpdate();

	private:
		Entity m_Current;
		Asset* m_Asset;

		int m_Mode = 0;

		bool m_UseTexture;

		void DrawEntity();
		void DrawAsset();
	};
}
