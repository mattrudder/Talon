#include "BufferTestSimulation.h"
#include <Talon/Graphics/BufferUsage.h>
using namespace Talon;

BufferTestSimulation::BufferTestSimulation()
	: m_vertexBuffer(nullptr)
	, m_indexBuffer(nullptr)
{
}

BufferTestSimulation::~BufferTestSimulation(void)
{
}

void BufferTestSimulation::OnBeginFrame()
{
	if (m_vertexBuffer == nullptr)
	{
		float verts[] = 
		{ 
			0, 1, 0, 0.5, 1.0,
			-1, -1, 0, 0.0, 0.0,
			1, -1, 0, 1.0, 0.0
		};
		m_vertexBuffer = Talon::make_unique<Talon::VertexBuffer>(Device, sizeof(float) * 5, 3, verts, BufferUsage::Default);
	}

	if (m_indexBuffer == nullptr)
	{
		short indicies[] = { 0, 1, 2 };
		m_indexBuffer = Talon::make_unique<Talon::IndexBuffer>(Device, 3, BufferFormat::I16, indicies, BufferUsage::Default);
	}
}

void BufferTestSimulation::OnEndFrame()
{

}