#include "GeometryData.h"

namespace geometry {
	GeometryData::GeometryData():
		vb(std::make_unique<VertexBuffer>()),
		vertexArray(std::make_unique<VertexArray>()),
		indexBuffer(std::make_unique<IndexBuffer>())
	{
	}

	void GeometryData::CreateVertexArray(
		const float cubeVertexBufferData[],
		const unsigned int cubeVertexBufferDataSize,
		const VertexBufferLayout& layout)
	{
		vb->Createbuffer(cubeVertexBufferData, cubeVertexBufferDataSize);
		vertexArray->AddBuffer(*vb, layout);
	}
	void GeometryData::CreateIndexBuffer(const unsigned int indices[], const unsigned int indicesSize)
	{
		indexBuffer->CreateBuffer(indices, indicesSize);
	}
}

