#pragma once
#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

union ShaderUniformValue
{
	float f3[3];
	float f4[4];
	float f;
	int i;
	glm::mat4 mat4;
	glm::vec3 vec3;
};

enum ShaderUniformType {
	f3 = 1,
	f4 = 2,
	f = 3,
	i = 4,
	mat4 = 5,
	vec3 = 6
};

struct UniformTypeAndValue
{
	ShaderUniformType type;
	ShaderUniformValue value;
};

class Shader
{
private:
	std::string m_Filepath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, unsigned int> m_UniformLocationCache;
	//caching for Uniforms
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// set Uniforms
	void SetUnifrom3f(const std::string& name, float v0, float v1, float v2);
	void SetUnifrom4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUnifrom1f(const std::string& name, float v);
	void SetUnifrom1i(const std::string& name, int v);
	void SetUnifromMat4f(const std::string& name, const glm::mat4& matrix);
	void SetUnifromVec3f(const std::string& name, const glm::vec3& vec3);
private:
	unsigned int GetUniformLocations(const std::string& name);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	ShaderProgramSource ParseShader(const std::string& filepath);
};