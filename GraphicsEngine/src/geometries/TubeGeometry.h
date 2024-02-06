#pragma once

#include <array>

#include "glm/glm.hpp"
#include "glm/ext/scalar_constants.hpp"

#include "GeometryData.h"
#include "VertexBufferLayout.h"
#include "IGeometry.h"

namespace geometry
{
	class TubeGeometry final : public IGeometry
	{
	private:
		std::vector<float>* tubeVertexBufferData;
		std::vector<unsigned int>* tubeIndexBufferData;

		GeometryData geometryData;
		VertexBufferLayout vbLayout;

		VertexBufferLayout GenerateLayout();

		void GenerateVertexBufferData(const std::vector<glm::vec3>& path, unsigned int segments, float radius, bool loop);

		void GenerateIndexBufferData(unsigned int pathPartCount, unsigned int segments, bool loop);

	public:
		TubeGeometry(const std::vector<glm::vec3>& path, unsigned int segments, float radius, bool loop = false);
		~TubeGeometry();

		inline const VertexArray& GetVertexArray() const { return geometryData.GetVertexArray(); };
		inline const IndexBuffer& GetIndexBuffer() const { return geometryData.GetIndexBuffer(); };
	};
}