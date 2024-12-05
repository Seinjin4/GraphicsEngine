#pragma once
#include <Renderer.h>
#include "cameras/PerspectiveCamera.h"
#include <memory>
#include <geometries/Mesh.h>
#include "SceneObject.h"

class NewScene
{
private:
	glm::mat4 view;
	camera::PerspectiveCamera camera;
	std::vector<SceneObject> m_sceneObjects;

public:
	NewScene();

	void RenderScene(const Renderer& renderer, glm::mat4 newView);
	void AddSceneObject(SceneObject&& mesh);
};

