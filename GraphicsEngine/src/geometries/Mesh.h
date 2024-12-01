#pragma once
#include "Shader.h"
#include "GeometryData.h"
#include <map>

namespace geometry
{
	class IMesh
	{
		virtual void Render(const Renderer& renderer) const = 0;
	};

	class Mesh : public IMesh
	{
	private:
		const GeometryData& m_data;
		Shader& m_shader;
		//std::vector<ShaderUniform> m_uniforms;
		std::map<std::string, UniformTypeAndValue> m_uniforms;

	public:
		Mesh( const GeometryData& data, Shader& shader, std::map<std::string, UniformTypeAndValue>&& uniforms);

		Mesh(const Mesh& other) = delete; //Placeholder until I figure out what the actual behavior should be
		Mesh& operator=(const Mesh& other) = delete;

		Mesh(const Mesh&& other) = delete;
		Mesh& operator=(const Mesh&& other) = delete;

		void Render(const Renderer& renderer) const override;

		std::map<std::string, UniformTypeAndValue>& GetUniforms();
	};

	class IMeshFactory
	{
	public:
		virtual std::unique_ptr<Mesh> CreateCubeMesh() = 0;
		//virtual Mesh CreateSphereMesh() = 0;
		//virtual Mesh CreatePlaneMesh() = 0;
		//virtual Mesh CreateCustomMesh(const GeometryData& data) = 0;
	};

	class MeshFactory : public IMeshFactory
	{
	private:
		GeometryDataFactory m_geometryDataFactory;
		std::map<std::string, Shader> m_shaderMap; //Temporary


	public:
		MeshFactory() = default;

		std::unique_ptr<Mesh> CreateCubeMesh() override;
		//Mesh CreateSphereMesh() override;
		//Mesh CreatePlaneMesh() override;
		//Mesh CreateCustomMesh(const GeometryData& data) override;
	};
}
