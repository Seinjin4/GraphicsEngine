#pragma once
#include "Shader.h"
#include "GeometryData.h"
#include "Mesh.h"
#include "StaticVertexData.h"

namespace geometry
{
	static void SetUniform(Shader& shader, std::string uniformName, const UniformTypeAndValue& uniform)
	{
		switch (uniform.type)
		{
		case ShaderUniformType::f3:
			shader.SetUnifrom3f(uniformName, uniform.value.f3[0], uniform.value.f3[1], uniform.value.f3[2]);
			break;
		case ShaderUniformType::f4:
			shader.SetUnifrom4f(uniformName, uniform.value.f4[0], uniform.value.f4[1], uniform.value.f4[2], uniform.value.f4[3]);
			break;
		case ShaderUniformType::i:
			shader.SetUnifrom1i(uniformName, uniform.value.i);
			break;
		case ShaderUniformType::f:
			shader.SetUnifrom1f(uniformName, uniform.value.f);
			break;
		case ShaderUniformType::mat4:
			shader.SetUnifromMat4f(uniformName, uniform.value.mat4);
			break;
		case ShaderUniformType::vec3:
			shader.SetUnifromVec3f(uniformName, uniform.value.vec3);
			break;
		}
	}

	Mesh::Mesh(const GeometryData& data, Shader& shader, std::map<std::string, UniformTypeAndValue>&& uniforms)
		: m_data(data), m_shader(shader), m_uniforms(std::move(uniforms))
	{
	}

	void Mesh::Render(const Renderer& renderer) const
	{
		m_shader.Bind();
		for(const auto& uniform : m_uniforms)
		{
			SetUniform(m_shader, uniform.first, uniform.second);
		};
		renderer.DrawTriangles(m_data.GetVertexArray(), m_data.GetIndexBuffer(), m_shader);
	}

	std::map<std::string, UniformTypeAndValue>& Mesh::GetUniforms()
	{
		return m_uniforms;
	}

	std::unique_ptr<Mesh> MeshFactory::CreateCubeMesh()
	{
		auto shaderMapEntry = m_shaderMap.find("ShadedColor");
		if (shaderMapEntry == m_shaderMap.end())
		{
			m_shaderMap.emplace("ShadedColor", "res/shaders/ShadedColor.shader");
			shaderMapEntry = m_shaderMap.find("ShadedColor");
		}

		std::map<std::string, UniformTypeAndValue> uniforms;

		uniforms.emplace("MVP", UniformTypeAndValue{ ShaderUniformType::mat4, ShaderUniformValue{ } });
		uniforms.emplace("lightPos", UniformTypeAndValue{ ShaderUniformType::vec3, ShaderUniformValue{ {0.0f, 5.0f, 0.0f} } });
		uniforms.emplace("viewPos", UniformTypeAndValue{ ShaderUniformType::vec3, ShaderUniformValue{} });
		uniforms.emplace("lightColor", UniformTypeAndValue{ ShaderUniformType::vec3, ShaderUniformValue{ {1.0f, 1.0f, 1.0f} } });
		uniforms.emplace("objectColor", UniformTypeAndValue{ ShaderUniformType::vec3, ShaderUniformValue{ {0.55f, 0.55f, 0.55f} } });

		return std::make_unique<Mesh>(m_geometryDataFactory.GetCubeGeometryData(), shaderMapEntry->second, std::move(uniforms));
	}

	//IMesh MeshFactory::CreateSphereMesh()
	//{
	//	return IMesh();
	//}
	//IMesh MeshFactory::CreatePlaneMesh()
	//{
	//	return IMesh();
	//}
	//IMesh MeshFactory::CreateCustomMesh(const GeometryData& data)
	//{
	//	return IMesh();
	//}
}
