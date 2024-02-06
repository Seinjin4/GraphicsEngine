#pragma once

#include "GeometryData.h"
#include "VertexBufferLayout.h"
#include "IGeometry.h"

namespace geometry
{
	class PlaneGeometry final : public IGeometry
	{
	private:
		std::vector<float>* planeVertexBufferData;
		std::vector<unsigned int>* planeIndexBufferData;

		GeometryData geometryData;
		VertexBufferLayout vbLayout;

		VertexBufferLayout GenerateLayout();

		void GenerateVertexBufferData(unsigned int segments);

		void GenerateIndexBufferData(unsigned int segments);

	public:
		PlaneGeometry(const unsigned int segments);
		~PlaneGeometry();

		inline const VertexArray& GetVertexArray() const { return geometryData.GetVertexArray(); };
		inline const IndexBuffer& GetIndexBuffer() const { return geometryData.GetIndexBuffer(); };
	};
}