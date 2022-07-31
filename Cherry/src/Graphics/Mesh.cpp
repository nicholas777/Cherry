#include "epch.h"
#include "Mesh.h"

#include "core/Core.h"
#include "core/Log.h"

#include <cstdint>

namespace Cherry
{
	static BufferLayout GenLayout(bool HasUV, bool hasColor)
	{
		if (hasColor)
		{
			return BufferLayout({
				{ "position", ShaderDataType::Float2 },
				{ "color", ShaderDataType::Float4 }
				});
		}
		else if (HasUV)
		{
			return BufferLayout({
				{ "position", ShaderDataType::Float2 },
				{ "UV", ShaderDataType::Float2 }
				});
		}

		return BufferLayout({
			{ "position", ShaderDataType::Float2 }
		});
	}

	Mesh::Mesh(VertexList vertices, std::vector<uint32_t> indices, Material* material)
	{
		float* dataRaw = GenerateRawData(vertices, vertices.size());
		
		BufferLayout layout = GenLayout(vertices.HasUVs(), vertices.HasColors());

		m_Vao = VertexArray::Create();
		m_Vao->AddVertexBuffer(dataRaw, vertices.size() / 4, layout);
		m_Vao->SetIndexBuffer(indices.data(), indices.size());

		m_Material = material;
	}

	void Mesh::Bind()
	{
		m_Material->Bind();
		m_Vao->Bind();
	}

	float* Mesh::GenerateRawData(VertexList vertices, int size)
	{
		float* dataRaw = new float[size / 4];

		int stride = vertices[0].size / 4;

		for (int i = 0; i < vertices.length(); i++)
		{
			dataRaw[i * stride]		= vertices[i].position.x;
			dataRaw[i * stride + 1] = vertices[i].position.y;

			if (vertices.HasColors())
			{
				dataRaw[i * stride + 2] = vertices[i].color.x;
				dataRaw[i * stride + 3] = vertices[i].color.y;
				dataRaw[i * stride + 4] = vertices[i].color.z;
				dataRaw[i * stride + 5] = vertices[i].color.w;
			}
			else if (vertices.HasUVs())
			{
				dataRaw[i * stride + 2] = vertices[i].TexCoord.x;
				dataRaw[i * stride + 3] = vertices[i].TexCoord.y;
			}
		}

		return dataRaw;
	}
}
