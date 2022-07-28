#include "epch.h"
#include "Renderer.h"

namespace Cherry
{
	Renderer::SceneData* Renderer::m_SceneData = new SceneData();

	void Renderer::Begin(Camera camera)
	{
		m_SceneData->VP = camera.CalcVP();
	}

	void Renderer::End()
	{
	}

	void Renderer::Submit(Mesh m, Matrix4x4f transform)
	{
		m.GetMaterial()->Set();
		m.GetMaterial()->GetShader()->SetMat4("VPMatrix", m_SceneData->VP);
		m.GetMaterial()->GetShader()->SetMat4("ModelMatrix", transform);

		RenderCommand::DrawElements(m);
	}
}