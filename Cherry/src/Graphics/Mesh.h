#pragma once

#include "Math/Vector.h"
#include "Vertex.h"

#include "Renderer/Buffers.h"
#include "Renderer/VertexArray.h"
#include "Material.h"

#include <vector>

namespace Cherry
{
	class CHERRY_API Mesh
	{
	public:
		Mesh() {};
		Mesh(VertexList vertices, std::vector<uint32_t> indices, Material* material);

		void Bind();

		inline VertexArray* GetVAO() { return m_Vao.Get(); }
		inline Material* GetMaterial() { return m_Material; }

	private:
		Scoped<VertexArray> m_Vao;
		Material* m_Material;

		float* GenerateRawData(VertexList vertices, int size);
	};
}