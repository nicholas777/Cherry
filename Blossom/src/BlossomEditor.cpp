#include "Cherry.h"

// HACK: EntryPoint included seperately to avoid multiple definitions of main()
#include "core/EntryPoint.h"
#include "EditorLayer.h"

namespace Cherry
{

	class BlossomEditor : public Application
	{
	public:
		BlossomEditor()
		{
			Configuration.Name = "Blossom Editor";

			Configuration.WindowWidth = 1200;
			Configuration.WindowHeight = 800;
			Configuration.WindowTitle = "Blossom Editor";
			Configuration.IsVSync = true;

			PushLayer(new EditorLayer());
		}

		~BlossomEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new BlossomEditor();
	}
}
