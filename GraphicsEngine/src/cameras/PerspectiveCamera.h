#pragma once

#include "Camera.h"


namespace camera
{
	class PerspectiveCamera : public Camera
	{
	private:
		float near;
		float far;
		float fov; //in radians
		float aspectRatio;

	public:
		PerspectiveCamera(const float fov,const float aspectRatio,const float near,const float far,const glm::mat4 view);
		PerspectiveCamera(const PerspectiveCamera&) = delete;

		void UpdateProjectionMatrix();

		inline float GetNear() const { return near; }
		inline float GetFar() const  { return far; }
		inline float GetFov() const  { return fov; }
		inline float GetAspectRatio() const  { return aspectRatio; }

		void SetNear(float near) { this->near = near; UpdateProjectionMatrix(); }
		void SetFar(float far) { this->far = far; UpdateProjectionMatrix(); }
		void SetFov(float fov) { this->fov = fov; UpdateProjectionMatrix(); }
		void SetAspectRatio(float aspectRatio) { this->aspectRatio = aspectRatio; UpdateProjectionMatrix(); }
	};
}