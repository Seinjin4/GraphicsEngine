#pragma once
#include <Renderer.h>
#include "cameras/PerspectiveCamera.h"
#include <memory>
#include <geometries/Mesh.h>

class NewScene
{
private:
	glm::mat4 view;
	camera::PerspectiveCamera camera;
	std::vector<std::unique_ptr<geometry::Mesh>> m_meshes;

public:
	NewScene();

	void RenderScene(const Renderer& renderer, glm::mat4 newView);
	void AddMesh(std::unique_ptr<geometry::Mesh>&& mesh);
};

