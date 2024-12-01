#include "VertexBuffer.h"

#include "Renderer.h"

VertexBuffer::VertexBuffer()
    : m_RendererID(std::make_unique<unsigned int>())
{
}

VertexBuffer::VertexBuffer(const void* data,const unsigned int size)
    : m_RendererID(std::make_unique<unsigned int>())
{
    GLCall(glGenBuffers(1, m_RendererID.get()));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, *m_RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
    :m_RendererID(std::move(other.m_RendererID))
{
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
    if (this != &other)
    {

        m_RendererID = std::move(other.m_RendererID);
    }
    return *this;
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, m_RendererID.get()));
}

void VertexBuffer::Createbuffer(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, m_RendererID.get()));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, *m_RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, *m_RendererID));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
