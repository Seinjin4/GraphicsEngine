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

		GeometryData(GeometryData&&) noexcept;
		GeometryData& operator=(GeometryData&&) noexcept;

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

	class GeometryDataCache
	{
	private:
		std::unordered_map<std::string, GeometryData> m_cache;

	public:
		GeometryDataCache() = default;
		GeometryDataCache(const GeometryDataCache&) = delete;
		GeometryDataCache operator=(const GeometryDataCache&) = delete;

		static GeometryDataCache& GetInstance();

		GeometryData* Get(const std::string& id);
		bool Put(std::string&& id, GeometryData&& geometryData);
	};

	class GeometryDataFactory
	{
	public:
		GeometryDataFactory() = default;
		GeometryDataFactory(const GeometryDataFactory&) = delete;
		GeometryDataFactory(GeometryDataFactory&&) = delete;

		GeometryDataFactory operator =(const GeometryDataFactory&) = delete;
		GeometryDataFactory operator =(GeometryDataFactory&&) = delete;

		GeometryData& GetCubeGeometryData();
		GeometryData& GetSphereGeometryData(unsigned int horizontalSegments, unsigned int verticalSegments);
	};

}