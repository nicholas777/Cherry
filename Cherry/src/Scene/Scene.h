#pragma once

#include "Graphics/Cameras/Camera.h"
#include "core/Pointer.h"
#include "core/Timestep.h"
#include "Renderer/Renderer2D.h"

#include "Component.h"

// TODO: EnTT include is broken
#include "../vendor/EnTT/entt.hpp"

namespace Cherry
{
	class Entity;

	class CHERRY_API Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity();

		void OnUpdate(const Timestep& delta);
	private:
		entt::registry m_Registry;

		// TODO: Multiple cameras, way of setting the projection matrix to pre-defined values, extending the CameraController class and clarify that Camera is an orthographic one.
		Scoped<Camera> m_Camera;

		friend class Entity;
	};
}
