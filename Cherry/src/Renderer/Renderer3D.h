#pragma once

#include "RenderCommand.h"
#include "Graphics/Camera.h"
#include "core/Pointer.h"
#include "utils/ShaderLibrary.h"
#include "Graphics/Mesh.h"

namespace Cherry
{
	class CHERRY_API Renderer3D
	{
	public:
		static void Init();

		static void Begin(Camera* camera);
		static void End();

		static void Submit(Mesh* m, Matrix4x4f* transform);

	private:
		struct SceneData 
		{
			Matrix4x4f VP;
		};

		static SceneData* m_SceneData;
	};
}
