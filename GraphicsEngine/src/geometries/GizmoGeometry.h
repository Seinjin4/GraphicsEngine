#pragma once

#include "GeometryData.h"
#include "VertexBufferLayout.h"
#include "IGeometry.h"

namespace geometry
{
	class GizmoGeometry final : public IGeometry
	{
	private:
		GeometryData geometryData;
		VertexBufferLayout vbLayout;

		void GenerateLayout();

	public:
		GizmoGeometry();

		inline const VertexArray& GetVertexArray() const { return geometryData.GetVertexArray(); };
		inline const IndexBuffer& GetIndexBuffer() const { return geometryData.GetIndexBuffer(); };
	};
}