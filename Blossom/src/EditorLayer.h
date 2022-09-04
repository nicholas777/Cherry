#pragma once

#include "Cherry.h"

#include "Graphics/UI/UIComponent.h"

namespace Cherry
{
	class EditorLayer : public Layer
	{
	public:

		virtual ~EditorLayer() override;

		virtual void OnAttach() override;
		virtual void OnUpdate(const Timestep& delta) override;

	private:
		Scoped<Texture> m_SmileTexture;

		Scoped<Font> m_Font;

		Scoped<Camera> m_EditorCamera;
		Scoped<Camera> m_LevelEditorCamera;
		Scoped<CameraController> m_LevelEditorCameraController;
	};
}