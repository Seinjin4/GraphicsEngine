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

	for (auto& sceneObject : m_sceneObjects)
	{
		sceneObject.Render(renderer, camera.GetProjectionView(), newView);
	}
}

void NewScene::AddSceneObject(SceneObject&& sceneObject)
{
	m_sceneObjects.push_back(std::move(sceneObject));
}
