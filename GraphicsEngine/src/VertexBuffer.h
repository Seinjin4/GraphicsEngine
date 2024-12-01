#pragma once
#include <memory>

class VertexBuffer
{
private:
	std::unique_ptr<unsigned int> m_RendererID;

public:
	VertexBuffer();
	VertexBuffer(const void* data, unsigned int size);

	VertexBuffer(const VertexBuffer&) = delete;
	VertexBuffer& operator=(const VertexBuffer&) = delete;

	VertexBuffer(VertexBuffer&&) noexcept;
	VertexBuffer& operator=(VertexBuffer&&) noexcept;

	~VertexBuffer();

	void Createbuffer(const void* data, unsigned int size);

	void Bind() const;
	void Unbind() const;
};