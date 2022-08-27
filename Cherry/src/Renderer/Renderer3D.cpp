#include "epch.h"
#include "Renderer3D.h"
#include "core/Pointer.h"

namespace Cherry
{
	Renderer3D::SceneData* Renderer3D::m_SceneData = new SceneData();

	void Renderer3D::Init()
	{
		RenderCommand::Init();
	}

	void Renderer3D::Begin(Camera* camera)
	{
		m_SceneData->VP = camera->CalcVP();
	}

	void Renderer3D::End()
	{
	}

	void Renderer3D::Submit(Mesh* m, Matrix4x4f* transform)
	{
		m->Bind();
		//m->GetMaterial()->Set("VPMatrix", m_SceneData->VP);
		//m->GetMaterial()->Set("ModelMatrix", *transform);

		RenderCommand::DrawElements(m->GetVAO());
	}

}
