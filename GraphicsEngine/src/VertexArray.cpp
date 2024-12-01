#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

VertexArray::VertexArray()
	: m_RendererID(std::make_unique<unsigned int>())
{
	GLCall(glGenVertexArrays(1, m_RendererID.get()));
	GLCall(glBindVertexArray(*m_RendererID));
}

VertexArray::VertexArray(const VertexBuffer& vb, const VertexBufferLayout& layout)
	: m_RendererID(std::make_unique<unsigned int>())
{
	GLCall(glGenVertexArrays(1, m_RendererID.get()));
	GLCall(glBindVertexArray(*m_RendererID));

	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));

		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

VertexArray::VertexArray(VertexArray&& other) noexcept
	:m_RendererID(std::move(other.m_RendererID))
{
}

VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
{
	if (this != &other)
	{

		m_RendererID = std::move(other.m_RendererID);
	}
	return *this;
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, m_RendererID.get()));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));

		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(*m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
