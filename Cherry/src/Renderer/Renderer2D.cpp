#include "epch.h"
#include "Renderer2D.h"

namespace Cherry
{
	struct RectVertex
	{
		Vector2f pos;
		Vector2f texCoord;
		float texSlot;
	};

	struct RendererData
	{
		const uint32_t MaxRects			= 8000;
		const uint32_t MaxVertices		= MaxRects * 4;
		const uint32_t MaxIndices		= MaxRects * 6;
		static const uint32_t MaxTextureSlots	= 16;

		Scoped<Shader> TextureShader;
		int Samplers[MaxTextureSlots];

		Scoped<VertexArray> BatchVAO;
		Scoped<VertexBuffer> BatchVBO;
		Scoped<IndexBuffer> BatchIndexBuffer;

		RectVertex* RectBase;
		RectVertex* RectPtr;

		uint32_t IndexCount;

		Vector4f RectVertices[4];

		uint32_t CurrentRects = 0;

		Scoped<Texture> WhiteTexture;
		std::array<Texture*, MaxTextureSlots> TextureSlots;
		float TextureSlotIndex = 1.0;
	};

	static RendererData* s_Data = new RendererData();

	void Renderer2D::Init()
	{
		s_Data->RectBase = new RectVertex[s_Data->MaxVertices];
		s_Data->RectPtr = s_Data->RectBase;

		s_Data->RectVertices[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data->RectVertices[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		s_Data->RectVertices[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		s_Data->RectVertices[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

		s_Data->BatchVAO = VertexArray::Create();
		s_Data->BatchVAO->Bind();

		s_Data->BatchVBO = VertexBuffer::Create(s_Data->MaxVertices * sizeof(RectVertex) / sizeof(float));

		s_Data->BatchVBO->SetLayout({
			{ "position", ShaderDataType::Float2 },
			{ "UV", ShaderDataType::Float2 },
			{ "TextureSlot", ShaderDataType::Float }
		});

		s_Data->BatchVAO->AddVertexBuffer(s_Data->BatchVBO.Get());

		uint32_t* indices = new uint32_t[s_Data->MaxIndices];

		uint32_t offset = 0;
		for (int i = 0; i < s_Data->MaxIndices; i += 6)
		{
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		s_Data->BatchIndexBuffer = IndexBuffer::Create(indices, s_Data->MaxIndices);
		s_Data->BatchVAO->SetIndexBuffer(s_Data->BatchIndexBuffer.Get());
		delete[] indices;

		s_Data->TextureShader = Shader::Create("assets/TextureShader.glsl");

		int Samplers[16] = {
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
		};

		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetIntArray("u_Samplers", Samplers, 16);

		uint32_t textureData = 0xffffffff;
		s_Data->WhiteTexture = Texture::Create(1, 1);
		s_Data->WhiteTexture->SetData(&textureData, sizeof(textureData));

		s_Data->TextureSlots[0] = s_Data->WhiteTexture.Get();
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}
	
	void Renderer2D::Begin(Camera* cam)
	{
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("VPMatrix", cam->CalcVP());
		NewBatch();
	}

	void Renderer2D::End()
	{
		Flush();
	}

	void Renderer2D::DrawRect(const Vector2f& position, const Vector2f& size, const Scoped<Texture>& texture)
	{
		if (s_Data->CurrentRects >= s_Data->MaxRects)
		{
			Flush();
			NewBatch();
		}

		float textureIndex = 0.0;

		for (uint32_t i = 0; i < s_Data->TextureSlotIndex; i++)
		{
			if (texture.Get() == s_Data->TextureSlots[i])
			{
				textureIndex = i;
				break;
			}
		}

		if (textureIndex == 0.0)
		{
			if (s_Data->TextureSlotIndex >= RendererData::MaxTextureSlots)
			{
				Flush();
				NewBatch();
			}

			textureIndex = s_Data->TextureSlotIndex;
			s_Data->TextureSlots[textureIndex] = texture.Get();
			s_Data->TextureSlotIndex++;
		}

		TransformationMatrix transform(position);
		transform.Scale(size);

		s_Data->RectPtr->pos = transform * s_Data->RectVertices[0];
		s_Data->RectPtr->texCoord = { 0.0f, 0.0f };
		s_Data->RectPtr->texSlot = textureIndex;
		s_Data->RectPtr++;

		s_Data->RectPtr->pos = transform * s_Data->RectVertices[1];
		s_Data->RectPtr->texCoord = { 1.0f, 0.0f };
		s_Data->RectPtr->texSlot = textureIndex;
		s_Data->RectPtr++;

		s_Data->RectPtr->pos = transform * s_Data->RectVertices[2];
		s_Data->RectPtr->texCoord = { 1.0f, 1.0f };
		s_Data->RectPtr->texSlot = textureIndex;
		s_Data->RectPtr++;
		
		s_Data->RectPtr->pos = transform * s_Data->RectVertices[3];
		s_Data->RectPtr->texCoord = { 0.0f, 1.0f };
		s_Data->RectPtr->texSlot = textureIndex;
		s_Data->RectPtr++;

		s_Data->IndexCount += 6;
		s_Data->CurrentRects++;
	}

	void Renderer2D::DrawRect(const Vector2f& position, const float& rotation, const Vector2f& size, const Scoped<Texture>& texture)
	{
		if (s_Data->IndexCount >= s_Data->MaxIndices)
		{
			Flush();
			NewBatch();
		}

		float textureIndex = 0;

		for (uint32_t i = 0; i < s_Data->TextureSlotIndex; i++)
		{
			if (texture.Get() == s_Data->TextureSlots[i])
			{
				textureIndex = i;
				break;
			}
		}

		if (textureIndex == 0.0)
		{
			if (s_Data->TextureSlotIndex >= RendererData::MaxTextureSlots)
			{
				Flush();
				NewBatch();
			}

			textureIndex = s_Data->TextureSlotIndex;
			s_Data->TextureSlots[textureIndex] = texture.Get();
			s_Data->TextureSlotIndex++;
		}

		TransformationMatrix transform(position);
		transform.Scale(size);
		transform.Rotate(rotation);

		s_Data->RectPtr->pos = transform * s_Data->RectVertices[0];
		s_Data->RectPtr->texCoord = { 0.0f, 0.0f };
		s_Data->RectPtr->texSlot = textureIndex;
		s_Data->RectPtr++;

		s_Data->RectPtr->pos = transform * s_Data->RectVertices[1];
		s_Data->RectPtr->texCoord = { 1.0f, 0.0f };
		s_Data->RectPtr->texSlot = textureIndex;
		s_Data->RectPtr++;

		s_Data->RectPtr->pos = transform * s_Data->RectVertices[2];
		s_Data->RectPtr->texCoord = { 1.0f, 1.0f };
		s_Data->RectPtr->texSlot = textureIndex;
		s_Data->RectPtr++;

		s_Data->RectPtr->pos = transform * s_Data->RectVertices[3];
		s_Data->RectPtr->texCoord = { 0.0f, 1.0f };
		s_Data->RectPtr->texSlot = textureIndex;
		s_Data->RectPtr++;

		s_Data->IndexCount += 6;
	}

	void Renderer2D::DrawRect(const Vector2f& position, const Vector2f& size, const SubTexture& texture)
	{
		if (s_Data->IndexCount >= s_Data->MaxIndices)
		{
			Flush();
			NewBatch();
		}

		float textureIndex = 0;

		for (uint32_t i = 0; i < s_Data->TextureSlotIndex; i++)
		{
			if (texture.texture == s_Data->TextureSlots[i])
			{
				textureIndex = i;
				break;
			}
		}

		if (textureIndex == 0.0)
		{
			if (s_Data->TextureSlotIndex >= RendererData::MaxTextureSlots)
			{
				Flush();
				NewBatch();
			}

			textureIndex = s_Data->TextureSlotIndex;
			s_Data->TextureSlots[textureIndex] = texture.texture;
			s_Data->TextureSlotIndex++;
		}

		TransformationMatrix transform(position);
		transform.Scale(size);

		s_Data->RectPtr->pos = transform * s_Data->RectVertices[0];
		s_Data->RectPtr->texCoord = texture.textureCoords[0];
		s_Data->RectPtr->texSlot = textureIndex;
		s_Data->RectPtr++;

		s_Data->RectPtr->pos = transform * s_Data->RectVertices[1];
		s_Data->RectPtr->texCoord = texture.textureCoords[1];
		s_Data->RectPtr->texSlot = textureIndex;
		s_Data->RectPtr++;

		s_Data->RectPtr->pos = transform * s_Data->RectVertices[2];
		s_Data->RectPtr->texCoord = texture.textureCoords[2];
		s_Data->RectPtr->texSlot = textureIndex;
		s_Data->RectPtr++;

		s_Data->RectPtr->pos = transform * s_Data->RectVertices[3];
		s_Data->RectPtr->texCoord = texture.textureCoords[3];
		s_Data->RectPtr->texSlot = textureIndex;
		s_Data->RectPtr++;

		s_Data->IndexCount += 6;
	}

	void Renderer2D::DrawRect(const Vector2f& position, const float& rotation, const Vector2f& size, const SubTexture& texture)
	{
		if (s_Data->IndexCount >= s_Data->MaxIndices)
		{
			Flush();
			NewBatch();
		}

		float textureIndex = 0;

		for (uint32_t i = 0; i < s_Data->TextureSlotIndex; i++)
		{
			if (texture.texture == s_Data->TextureSlots[i])
			{
				textureIndex = i;
				break;
			}
		}

		if (textureIndex == 0.0)
		{
			if (s_Data->TextureSlotIndex >= RendererData::MaxTextureSlots)
			{
				Flush();
				NewBatch();
			}

			textureIndex = s_Data->TextureSlotIndex;
			s_Data->TextureSlots[textureIndex] = texture.texture;
			s_Data->TextureSlotIndex++;
		}

		TransformationMatrix transform(position);
		transform.Scale(size);
		transform.Rotate(rotation);

		s_Data->RectPtr->pos = transform * s_Data->RectVertices[0];
		s_Data->RectPtr->texCoord = texture.textureCoords[0];
		s_Data->RectPtr->texSlot = textureIndex;
		s_Data->RectPtr++;

		s_Data->RectPtr->pos = transform * s_Data->RectVertices[1];
		s_Data->RectPtr->texCoord = texture.textureCoords[1];
		s_Data->RectPtr->texSlot = textureIndex;
		s_Data->RectPtr++;

		s_Data->RectPtr->pos = transform * s_Data->RectVertices[2];
		s_Data->RectPtr->texCoord = texture.textureCoords[2];
		s_Data->RectPtr->texSlot = textureIndex;
		s_Data->RectPtr++;

		s_Data->RectPtr->pos = transform * s_Data->RectVertices[3];
		s_Data->RectPtr->texCoord = texture.textureCoords[3];
		s_Data->RectPtr->texSlot = textureIndex;
		s_Data->RectPtr++;

		s_Data->IndexCount += 6;
	}

	void Renderer2D::Flush()
	{
		uint32_t dataSize = (uint32_t)((uint8_t*)s_Data->RectPtr - (uint8_t*)s_Data->RectBase);
		s_Data->BatchVBO->InsertData(s_Data->RectBase, dataSize, 0);

		for (uint32_t i = 0; i < s_Data->TextureSlotIndex; i++)
		{
			s_Data->TextureSlots[i]->Bind(i);
		}

		s_Data->BatchVAO->Bind();
		RenderCommand::DrawElements(s_Data->BatchVAO.Get(), s_Data->IndexCount);
	}

	void Renderer2D::NewBatch()
	{
		s_Data->CurrentRects = 0;
		s_Data->IndexCount = 0;

		s_Data->RectPtr = s_Data->RectBase;
		s_Data->TextureSlotIndex = 1;
	}

}