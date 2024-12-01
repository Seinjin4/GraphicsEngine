#include "NewScene.h"

NewScene::NewScene()
	:view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
	camera(glm::radians(45.0f), (GLfloat)1080.0f / (GLfloat)1080.0f, 0.1f, 150.0f, view)
{

}

void NewScene::RenderScene(const Renderer& renderer, glm::mat4 newView)
{
	glm::mat4& view = camera.GetView();
	view = newView;

	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 mvp = camera.GetProjectionView() * model;

	for (auto& mesh : m_meshes)
	{
		auto& uniforms = mesh->GetUniforms();

		auto uniformMVP = uniforms.find("MVP");
		uniformMVP->second.value.mat4 = mvp;

		auto uniformVIEWPOS = uniforms.find("viewPos");
		uniformVIEWPOS->second.value.vec3 = view[3];
	}

	for (auto& mesh : m_meshes)
	{
		mesh->Render(renderer);
	}
}

void NewScene::AddMesh(std::unique_ptr<geometry::Mesh>&& mesh)
{
	m_meshes.push_back(std::move(mesh));
}
