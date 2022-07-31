#include "epch.h"
#include "Renderer2D.h"

namespace Cherry
{
	struct RendererData
	{
		Scoped<VertexArray> SquareVAO;

		Scoped<Shader> ColorShader;
		Scoped<Shader> TextureShader;
	};

	static RendererData s_Data;

	void Renderer2D::Init()
	{
		float SquareVertices[8] =
		{
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f
		};

		uint32_t indices[6] =
		{
			0, 1, 2,
			2, 3, 0
		};

		BufferLayout layout = {
			{ "position", ShaderDataType::Float2 }
		};

		s_Data.SquareVAO = VertexArray::Create();
		s_Data.SquareVAO->AddVertexBuffer(SquareVertices, 8, layout);

		s_Data.SquareVAO->SetIndexBuffer(indices, 6);

		s_Data.ColorShader = Shader::Create("assets/ColorShader.glsl");
		s_Data.TextureShader = Shader::Create("assets/TextureShader.glsl");

		RenderCommand::Init();
	}
	
	void Renderer2D::Begin(Camera* cam)
	{
		
	}

	void Renderer2D::End()
	{
	}
	void Renderer2D::DrawRect(Matrix4x4f* transform, Vector4f color)
	{
	}

	void Renderer2D::DrawRect(Matrix4x4f* transform, const Scoped<Texture*>& color)
	{
	}
}