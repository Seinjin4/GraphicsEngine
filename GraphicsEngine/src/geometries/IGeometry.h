#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

namespace geometry
{
	class IGeometry
	{
	public:
		virtual const VertexArray& GetVertexArray() const = 0;
		virtual const IndexBuffer& GetIndexBuffer() const = 0;
	};
}