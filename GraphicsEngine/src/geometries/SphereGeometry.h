#pragma once

#include <array>

#include "glm/glm.hpp"
#include "glm/ext/scalar_constants.hpp"

#include "GeometryData.h"
#include "VertexBufferLayout.h"
#include "IGeometry.h"

namespace geometry
{
	class SphereGeometry final : public IGeometry
	{
	private:
		std::unique_ptr<std::vector<float>> sphereVertexBufferData;
		std::unique_ptr < std::vector<unsigned int>> sphereIndexBufferData;

		GeometryData geometryData;
		VertexBufferLayout vbLayout;

		VertexBufferLayout GenerateLayout();

		void GenerateVertexBufferData(float ratio, unsigned int verticalSegments, unsigned int horizontalSegments);

		void GenerateIndexBufferData(float ratio, unsigned int verticalSegments, unsigned int horizontalSegments);

	public:
		SphereGeometry(float ratio, unsigned int verticalSegments = 10, unsigned int horizontalSegments = 10);

		inline const VertexArray& GetVertexArray() const { return geometryData.GetVertexArray(); };
		inline const IndexBuffer& GetIndexBuffer() const { return geometryData.GetIndexBuffer(); };

		static std::vector<unsigned int> GenerateIndexBuffer(unsigned int verticalSegments, unsigned int horizontalSegments);
		static std::vector<float> GenerateVertexBuffer(float ratio, unsigned int verticalSegments, unsigned int horizontalSegments);
	};
}
