
#include "TalonPrefix.h"
#include <GL/glew.h>
#include <Talon/Graphics/OpenGL/GLIndexBuffer.h>

namespace Talon
{
	GLIndexBuffer::GLIndexBuffer(RenderDevice* renderDevice, int indexCount, BufferFormat format, void* initialData, BufferUsage bufferUsage)
		: Base(renderDevice, indexCount, format, initialData, bufferUsage)
		, m_elementBuffer(0)
	{
#pragma warning(push)
#pragma warning(disable : 4127)
		TALON_ASSERT(bufferUsage == BufferUsage::Dynamic || bufferUsage == BufferUsage::Default);
#pragma warning(pop)

		size_t indexSize = format == BufferFormat::I16 ? sizeof(short) : sizeof(int);
		glGenBuffers(1, &m_elementBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * indexCount, initialData, bufferUsage == BufferUsage::Dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	}

	GLIndexBuffer::~GLIndexBuffer()
	{
		glDeleteBuffers(1, &m_elementBuffer);
		m_elementBuffer = 0;
	}
}