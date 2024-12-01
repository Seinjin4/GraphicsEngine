#include "IndexBuffer.h"

#include "Renderer.h"

IndexBuffer::IndexBuffer()
    : m_RendererID(std::make_unique<unsigned int>())
{
}

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : m_RendererID(std::make_unique<unsigned int>())
    , m_Count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, m_RendererID.get()));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
    : m_RendererID(std::move(other.m_RendererID))
    , m_Count(other.m_Count)
{
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
{
    if (this != &other)
    {
        m_RendererID = std::move(other.m_RendererID);
        m_Count = other.m_Count;
    }
    return *this;
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, m_RendererID.get()));
}

void IndexBuffer::CreateBuffer(const unsigned int* data, unsigned int count)
{
    m_Count = count;

    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, m_RendererID.get()));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_RendererID));
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
