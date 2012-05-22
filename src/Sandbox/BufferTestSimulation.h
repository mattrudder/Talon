#pragma once

#include <Talon/Simulation.h>
#include <Talon/Graphics/IndexBuffer.h>
#include <Talon/Graphics/VertexBuffer.h>

class BufferTestSimulation : public Talon::Simulation
{
public:
	BufferTestSimulation(void);
	virtual ~BufferTestSimulation(void);

protected:
	void OnBeginFrame();
	void OnEndFrame();

private:
	std::unique_ptr<Talon::VertexBuffer> m_vertexBuffer;
	std::unique_ptr<Talon::IndexBuffer> m_indexBuffer;
};

