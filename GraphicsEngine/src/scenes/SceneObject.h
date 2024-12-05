#pragma once
#include <geometries/Mesh.h>
#include <glm/ext/vector_float3.hpp>
class SceneObject
{
private:
	std::unique_ptr<geometry::Mesh> m_mesh;
	glm::vec3 m_position;

public:
	SceneObject(std::unique_ptr<geometry::Mesh>&& mesh, glm::vec3&& position);

	SceneObject(const SceneObject&) = delete;
	SceneObject& operator=(const SceneObject&) = delete;

	SceneObject(SceneObject&&) noexcept;
	SceneObject& operator=(SceneObject&&) noexcept;

	void Render(const Renderer& renderer, glm::mat4 projView, glm::mat4 view);

	geometry::Mesh& GetMesh();
};

