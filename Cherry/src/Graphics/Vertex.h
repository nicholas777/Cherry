#pragma once

#include "Math/Vector.h"

#include "core/Core.h"
#include "core/Log.h"

namespace Cherry
{
	// TODO: Rewrite Vertex, VertexList and Mesh using buffers
	struct Vertex
	{
		Vector2f position;

		Vector4f color;
		bool hasColor = false;

		Vector2f TexCoord;
		bool hasTexCoord;

		int size;

		Vertex(Vector2f pos)
			: position(pos), size(8)
		{
		}

		Vertex(Vector2f pos, Vector4f vertexColor)
			: position(pos), color(vertexColor), size(24)
		{
			hasColor = true;
		}

		Vertex(Vector2f pos, Vector2f TextureCoordinate)
			: position(pos), TexCoord(TextureCoordinate), size(16)
		{
			hasTexCoord = true;
		}
	};

	struct VertexList
	{
		VertexList(std::initializer_list<Vertex> vertices)
			: m_Vertices(vertices)
		{
			int lastSize = m_Vertices[0].size;
			for (Vertex v : m_Vertices)
			{
				if (v.size != lastSize)
				{
					CH_CORE_ERROR("Invalid vertices while creating Mesh");
					CH_ASSERT(false, "Invalid vertices while creating Mesh");
					m_Vertices = std::vector<Vertex>();
					return;
				}
			}

			m_VertexColor = m_Vertices[0].hasColor;
			m_TextureCoordinate = m_Vertices[0].hasTexCoord;

			m_VertexSize = m_Vertices[0].size;
		}

		int size() { return m_Vertices.size() * m_VertexSize; };
		int length() { return m_Vertices.size(); }

		bool HasColors() { return m_VertexColor; }
		bool HasUVs() { return m_TextureCoordinate; }

		Vertex operator[](int index)
		{
			return m_Vertices[index];
		}

	private:
		std::vector<Vertex> m_Vertices;
		uint32_t m_VertexSize;

		bool m_VertexColor = false;
		bool m_TextureCoordinate = false;
	};
}