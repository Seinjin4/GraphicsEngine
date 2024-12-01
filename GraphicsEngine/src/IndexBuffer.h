#pragma once
#include <memory>

class IndexBuffer
{
private:
	std::unique_ptr<unsigned int> m_RendererID;
	unsigned int m_Count;

public:
	IndexBuffer();
	IndexBuffer(const unsigned int* data, unsigned int count);

	IndexBuffer(const IndexBuffer&) = delete;
	IndexBuffer& operator=(const IndexBuffer&) = delete;

	IndexBuffer(IndexBuffer&&) noexcept;
	IndexBuffer& operator=(IndexBuffer&&) noexcept;

	~IndexBuffer();

	void CreateBuffer(const unsigned int* data, unsigned int count);

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }
};