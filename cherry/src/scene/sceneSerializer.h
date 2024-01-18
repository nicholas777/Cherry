#pragma once

#include "scene.h"
#include "core/pointer.h"

namespace Cherry
{
	class SceneSerializer
	{
	public:
		static void Serialize(Shared<Scene> scene, const std::string& filepath);
		static Scene* Deserialize(const std::string& filepath);
	};
}
