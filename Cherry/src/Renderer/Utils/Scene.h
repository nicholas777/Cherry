#pragma once

#include "Graphics/Cameras/Camera.h"
#include "core/Pointer.h"

namespace Cherry
{
	struct Scene
	{
		Scoped<Camera> camera;
	};
}
