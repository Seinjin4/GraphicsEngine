#include "SceneObject.h"
#include <glm/ext/matrix_transform.hpp>

SceneObject::SceneObject(std::unique_ptr<geometry::Mesh>&& mesh, glm::vec3&& position)
	:m_mesh(std::move(mesh)), m_position(std::move(position))
{
}

SceneObject::SceneObject(SceneObject&& other) noexcept
	: m_mesh(std::move(other.m_mesh)), m_position(std::move(other.m_position))
{
}

SceneObject& SceneObject::operator=(SceneObject&& other) noexcept
{
	if (this != &other)
	{
		m_mesh = std::move(other.m_mesh);
		m_position = std::move(other.m_position);
	}
	return *this;
}



void SceneObject::Render(const Renderer& renderer, glm::mat4 projView, glm::mat4 view)
{
	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_position);
	glm::mat4 mvp = projView * model;

	auto& uniforms = m_mesh->GetUniforms();

	auto uniformMVP = uniforms.find("MVP");
	uniformMVP->second.value.mat4 = mvp;

	auto uniformVIEWPOS = uniforms.find("viewPos");
	uniformVIEWPOS->second.value.vec3 = view[3];

	m_mesh->Render(renderer);
}

geometry::Mesh& SceneObject::GetMesh()
{
	return *m_mesh;
}
