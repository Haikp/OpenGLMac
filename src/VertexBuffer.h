#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	// VertexBuffer(std::vector<Vertex>& vertices);
	VertexBuffer(unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};
