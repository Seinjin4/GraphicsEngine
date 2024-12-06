#include "SphereGeometry.h"

namespace geometry
{
	VertexBufferLayout SphereGeometry::GenerateLayout()
	{
		vbLayout.Push<float>(3);
		vbLayout.Push<float>(3);

		return vbLayout;
	}

	void SphereGeometry::GenerateVertexBufferData(float ratio, unsigned int verticalSegments, unsigned int horizontalSegments)
	{
		sphereVertexBufferData->push_back(0.0f);
		sphereVertexBufferData->push_back(ratio);
		sphereVertexBufferData->push_back(0.0f);

		sphereVertexBufferData->push_back(0.0f);
		sphereVertexBufferData->push_back(1.0f);
		sphereVertexBufferData->push_back(0.0f);

		for (size_t i = 0; i < verticalSegments; i++)
		{
			//float newYCoordinate = ratio - ((float)(i + 1) / (verticalSegments + 1)) * 2 * ratio;
			float newYCoordinate = ratio * glm::cos(glm::pi<float>() * (float)(i + 1) / verticalSegments);
			float segmentRatio = ratio * glm::sin(glm::pi<float>() * (float)(i + 1) / verticalSegments);

			for (size_t j = 0; j < horizontalSegments; j++)
			{
				glm::vec3 newPoint( 
					glm::sin(glm::pi<float>() * 2 * j / horizontalSegments) * segmentRatio,
					newYCoordinate,
					glm::cos(glm::pi<float>() * 2 * j / horizontalSegments) * segmentRatio
				);

				sphereVertexBufferData->push_back(newPoint.x);
				sphereVertexBufferData->push_back(newPoint.y);
				sphereVertexBufferData->push_back(newPoint.z);

				glm::vec3 newPointNormal = glm::normalize(newPoint);

				sphereVertexBufferData->push_back(newPointNormal.x);
				sphereVertexBufferData->push_back(newPointNormal.y);
				sphereVertexBufferData->push_back(newPointNormal.z);
			}
		}

		sphereVertexBufferData->push_back(0.0f);
		sphereVertexBufferData->push_back(-ratio);
		sphereVertexBufferData->push_back(0.0f);

		sphereVertexBufferData->push_back(0.0f);
		sphereVertexBufferData->push_back(-1.0f);
		sphereVertexBufferData->push_back(0.0f);
	}

	std::vector<float> SphereGeometry::GenerateVertexBuffer(float ratio, unsigned int verticalSegments, unsigned int horizontalSegments)
	{
		std::vector<float> sphereVertexBuffer;
		//sphereVertexBuffer.resize(6 * 2 + verticalSegments * horizontalSegments * 6);

		sphereVertexBuffer.push_back(0.0f);
		sphereVertexBuffer.push_back(ratio);
		sphereVertexBuffer.push_back(0.0f);

		sphereVertexBuffer.push_back(0.0f);
		sphereVertexBuffer.push_back(1.0f);
		sphereVertexBuffer.push_back(0.0f);

		for (size_t i = 0; i < verticalSegments; i++)
		{
			//float newYCoordinate = ratio - ((float)(i + 1) / (verticalSegments + 1)) * 2 * ratio;
			float newYCoordinate = ratio * glm::cos(glm::pi<float>() * (float)(i + 1) / verticalSegments);
			float segmentRatio = ratio * glm::sin(glm::pi<float>() * (float)(i + 1) / verticalSegments);

			for (size_t j = 0; j < horizontalSegments; j++)
			{
				glm::vec3 newPoint(
					glm::sin(glm::pi<float>() * 2 * j / horizontalSegments) * segmentRatio,
					newYCoordinate,
					glm::cos(glm::pi<float>() * 2 * j / horizontalSegments) * segmentRatio
				);

				sphereVertexBuffer.push_back(newPoint.x);
				sphereVertexBuffer.push_back(newPoint.y);
				sphereVertexBuffer.push_back(newPoint.z);

				glm::vec3 newPointNormal = glm::normalize(newPoint);

				sphereVertexBuffer.push_back(newPointNormal.x);
				sphereVertexBuffer.push_back(newPointNormal.y);
				sphereVertexBuffer.push_back(newPointNormal.z);
			}
		}

		sphereVertexBuffer.push_back(0.0f);
		sphereVertexBuffer.push_back(-ratio);
		sphereVertexBuffer.push_back(0.0f);

		sphereVertexBuffer.push_back(0.0f);
		sphereVertexBuffer.push_back(-1.0f);
		sphereVertexBuffer.push_back(0.0f);

		return sphereVertexBuffer;
	}

	void SphereGeometry::GenerateIndexBufferData(float ratio, unsigned int verticalSegments, unsigned int horizontalSegments)
	{
		for (size_t x = 0; x < horizontalSegments; x++)
		{
			sphereIndexBufferData->push_back(0);
			sphereIndexBufferData->push_back(1 + x);
			sphereIndexBufferData->push_back(1 + (x + 1) % horizontalSegments);
		}

		for (size_t y = 0; y < verticalSegments - 1; y++)
		{
			for (size_t x = 0; x < horizontalSegments; x++)
			{
				sphereIndexBufferData->push_back(1 + y * horizontalSegments + x);
				sphereIndexBufferData->push_back(1 + (y + 1) * horizontalSegments + x);
				sphereIndexBufferData->push_back(1 + y * horizontalSegments + (x + 1) % horizontalSegments);

				sphereIndexBufferData->push_back(1 + y * horizontalSegments + (x + 1) % horizontalSegments);
				sphereIndexBufferData->push_back(1 + (y + 1) * horizontalSegments + x);
				sphereIndexBufferData->push_back(1 + (y + 1) * horizontalSegments + (x + 1) % horizontalSegments);
			}
		}

		for (size_t x = 0; x < horizontalSegments; x++)
		{
			sphereIndexBufferData->push_back(1 + (verticalSegments - 1) * horizontalSegments + x);
			sphereIndexBufferData->push_back(1 + verticalSegments * horizontalSegments);
			sphereIndexBufferData->push_back(1 + (verticalSegments - 1) * horizontalSegments + (x + 1) % horizontalSegments);
		}
	}

	std::vector<unsigned int> SphereGeometry::GenerateIndexBuffer(unsigned int verticalSegments, unsigned int horizontalSegments)
	{
		std::vector<unsigned int> sphereIndexBuffer;
		//sphereIndexBuffer.resize(2 * 3 * horizontalSegments + verticalSegments * horizontalSegments * 6);

		for (size_t x = 0; x < horizontalSegments; x++)
		{
			sphereIndexBuffer.push_back(0);
			sphereIndexBuffer.push_back(1 + x);
			sphereIndexBuffer.push_back(1 + (x + 1) % horizontalSegments);
		}

		for (size_t y = 0; y < verticalSegments - 1; y++)
		{
			for (size_t x = 0; x < horizontalSegments; x++)
			{
				sphereIndexBuffer.push_back(1 + y * horizontalSegments + x);
				sphereIndexBuffer.push_back(1 + (y + 1) * horizontalSegments + x);
				sphereIndexBuffer.push_back(1 + y * horizontalSegments + (x + 1) % horizontalSegments);

				sphereIndexBuffer.push_back(1 + y * horizontalSegments + (x + 1) % horizontalSegments);
				sphereIndexBuffer.push_back(1 + (y + 1) * horizontalSegments + x);
				sphereIndexBuffer.push_back(1 + (y + 1) * horizontalSegments + (x + 1) % horizontalSegments);
			}
		}

		for (size_t x = 0; x < horizontalSegments; x++)
		{
			sphereIndexBuffer.push_back(1 + (verticalSegments - 1) * horizontalSegments + x);
			sphereIndexBuffer.push_back(1 + verticalSegments * horizontalSegments);
			sphereIndexBuffer.push_back(1 + (verticalSegments - 1) * horizontalSegments + (x + 1) % horizontalSegments);
		}

		return sphereIndexBuffer;
	}

	SphereGeometry::SphereGeometry(float ratio, unsigned int verticalSegments, unsigned int horizontalSegments) :
		sphereVertexBufferData(std::make_unique<std::vector<float>>()),
		sphereIndexBufferData(std::make_unique<std::vector<unsigned int>>())
	{
		GenerateVertexBufferData(ratio, verticalSegments, horizontalSegments);
		GenerateIndexBufferData(ratio, verticalSegments, horizontalSegments);
		GenerateLayout();

		geometryData.CreateVertexArray(sphereVertexBufferData->data(), sphereVertexBufferData->size() * sizeof(float), vbLayout);
		geometryData.CreateIndexBuffer(sphereIndexBufferData->data(), sphereIndexBufferData->size());
	}
}