#include "GeometryData.h"
#include "StaticVertexData.h"
#include "CubeGeometry.h"

namespace geometry {

	//Standart layout is 3floats for a position and 3 floats for a normal.
	static VertexBufferLayout GenerateStandartLayout()
	{
		VertexBufferLayout vbLayout;

		vbLayout.Push<float>(3);
		vbLayout.Push<float>(3);

		return vbLayout;
	}

	GeometryData::GeometryData()
		: vb(std::make_unique<VertexBuffer>()),
		vertexArray(std::make_unique<VertexArray>()),
		indexBuffer(std::make_unique<IndexBuffer>())
	{
	}

	GeometryData::GeometryData(GeometryData&& other) noexcept
		: vb(std::move(other.vb)),
		vertexArray(std::move(other.vertexArray)),
		indexBuffer(std::move(other.indexBuffer))
	{

	}

	GeometryData& GeometryData::operator=(GeometryData&& other) noexcept
	{
		if (this != &other) 
		{
			vb = std::move(other.vb);
			vertexArray = std::move(other.vertexArray);
			indexBuffer = std::move(other.indexBuffer);
		}
		return *this;
	}

	void GeometryData::CreateVertexArray(
		const float vertexBufferData[],
		const unsigned int vertexBufferDataSize,
		const VertexBufferLayout& layout)
	{
		vb->Createbuffer(vertexBufferData, vertexBufferDataSize);
		vertexArray->AddBuffer(*vb, layout);
	}

	void GeometryData::CreateIndexBuffer(const unsigned int indices[], const unsigned int indicesSize)
	{
		indexBuffer->CreateBuffer(indices, indicesSize);
	}

	GeometryData& GeometryDataFactory::GetCubeGeometryData()
	{
		auto cacheResult = GeometryDataCache::GetInstance().Get("cube");
		if (cacheResult != nullptr)
			return *cacheResult;

		GeometryData geometryData;

		//geometryData.CreateVertexArray(geometry::cubeVertexBufferData, 216 * sizeof(float), GenerateStandartLayout());
		//geometryData.CreateIndexBuffer(geometry::cubeIndexBufferData, 36);
		
		geometryData.CreateVertexArray(VertexData::CubeVertexBufferData, VertexData::CubeVertexBufferData_SIZE * sizeof(float), GenerateStandartLayout());
		geometryData.CreateIndexBuffer(VertexData::CubeIndexBufferData, VertexData::CubeIndexBufferData_SIZE);

		GeometryDataCache::GetInstance().Put("cube", std::move(geometryData));

		cacheResult = GeometryDataCache::GetInstance().Get("cube");
		if (cacheResult == nullptr)
		{
			//TODO: ASSERT FASLE HERE
			//return assert(false);
		}

		return *cacheResult;
	}

	GeometryDataCache& GeometryDataCache::GetInstance()
	{
		static GeometryDataCache instance;
		return instance;
	}

	GeometryData* GeometryDataCache::Get(const std::string& id)
	{
		auto cacheResult = m_cache.find(id);
		if (cacheResult != m_cache.end())
		{
			return &cacheResult->second;
		}

		return nullptr;
	}

	bool GeometryDataCache::Put(std::string&& id, GeometryData&& geometryData)
	{
		if (Get(id) != nullptr)
			return false;

		m_cache.emplace(std::move(id), std::move(geometryData));
		return true;
	}
}

