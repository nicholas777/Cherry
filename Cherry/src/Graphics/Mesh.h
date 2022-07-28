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

		inline VertexArray* GetVAO() { return Vao; }
		inline Material* GetMaterial() { return m_Material; }

	private:
		VertexArray* Vao;
		Material* m_Material;

		float* GenerateRawData(VertexList vertices, int size);
	};
}