#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include <memory>

namespace geometry
{
	class GeometryData final
	{
	private:
		std::unique_ptr<VertexBuffer> vb;

		std::unique_ptr<VertexArray> vertexArray;
		std::unique_ptr<IndexBuffer> indexBuffer;

	public:
		GeometryData();
		GeometryData(const GeometryData&) = delete;
		GeometryData& operator=(const GeometryData&) = delete;


		void CreateVertexArray (
			const float cubeVertexBufferData[],
			const unsigned int cubeVertexBufferDataSize,
			const VertexBufferLayout& layout
		);

		void CreateIndexBuffer (
			const unsigned int indices[],
			const unsigned int indicesSize
		);

		inline const VertexArray& GetVertexArray() const { return *vertexArray; };
		inline const IndexBuffer& GetIndexBuffer() const { return *indexBuffer; };
	};
}