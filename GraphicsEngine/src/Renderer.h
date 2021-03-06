#pragma once

#include <Gl/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    void Clear() const;
    void Bind(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void DrawTriangles(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void DrawLineStrip(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const float lineWidth) const;
    void DrawLines(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const float lineWidth) const;

    void ToggleWireFrame(bool state) const;
    void SetClearColor(glm::vec4 color) const;
private:
    void EnableDepthTest() const;
};
