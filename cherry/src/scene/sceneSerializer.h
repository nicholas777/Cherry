#pragma once

#include "core/pointer.h"
#include "scene.h"

namespace Cherry {
    class SceneSerializer
    {
    public:
        static void Serialize(Scene* scene, const std::string& filepath);
        static Scene* Deserialize(const std::string& filepath);
    };
}
