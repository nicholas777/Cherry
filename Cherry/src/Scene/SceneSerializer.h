#pragma once

#include "Scene.h"
#include "core/Pointer.h"

#include <yaml-cpp/yaml.h>

namespace Cherry
{
	class SceneSerializer
	{
	public:
		static void Serialize(Shared<Scene> scene, const std::string& filepath);
		static Scene* Deserialize(const std::string& filepath);
	};
}
