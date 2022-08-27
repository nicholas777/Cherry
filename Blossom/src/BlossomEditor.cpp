#include "Cherry.h"
#include "EditorLayer.h"

using namespace Cherry;

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
	}

	~BlossomEditor()
	{

	}
};