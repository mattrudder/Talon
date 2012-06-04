#include "BufferTestSimulation.h"

#include <Talon/Engine.h>
#include <Talon/Input/InputService.h>
#include <Talon/Input/InputDevice.h>
#include <Talon/Graphics/BufferUsage.h>
#include <Talon/Graphics/Texture.h>
#include <Talon/Graphics/IndexBuffer.h>
#include <Talon/Graphics/VertexBuffer.h>

#include <Talon/Input/GamepadInputDevice.h>
#include <Talon/Input/KeyboardInputDevice.h>
#include <Talon/Input/MouseInputDevice.h>

#include <windows.h>

using namespace std;
using namespace Talon;

BufferTestSimulation::BufferTestSimulation()
	: m_engine(Engine::Instance())
	, m_vertexBuffer(nullptr)
	, m_indexBuffer(nullptr)
	, m_gamepad(nullptr)
	, m_keyboard(nullptr)
	, m_mouse(nullptr)
{
}

BufferTestSimulation::~BufferTestSimulation(void)
{
}

void BufferTestSimulation::Foo()
{
	OutputDebugStringA("Button pressed!");
}

void BufferTestSimulation::OnInitialized()
{
	m_engine->GetInputService()->DeviceConnected += [this](InputDevice* device)
	{
		InputDeviceType type = device->GetType();
		if (type == InputDeviceType::Gamepad && m_gamepad == nullptr)
			m_gamepad = static_cast<GamepadInputDevice*>(device);
		else if (type == InputDeviceType::Keyboard && m_keyboard == nullptr)
			m_keyboard = static_cast<KeyboardInputDevice*>(device);
		else if (type == InputDeviceType::Mouse && m_mouse == nullptr)
			m_mouse = static_cast<MouseInputDevice*>(device);
	};

	m_engine->GetInputService()->DeviceDisconnected += [this](InputDevice* device)
	{
		u32 id = device->GetId();
		InputDeviceType type = device->GetType();
		if (type == InputDeviceType::Gamepad && m_gamepad != nullptr && m_gamepad->GetId() == id)
			m_gamepad = nullptr;
		else if (type == InputDeviceType::Keyboard && m_keyboard != nullptr && m_keyboard->GetId() == id)
			m_keyboard = nullptr;
		else if (type == InputDeviceType::Mouse && m_mouse != nullptr && m_mouse->GetId() == id)
			m_mouse = nullptr;
	};
}

void BufferTestSimulation::OnBeginFrame()
{
	if (m_vertexBuffer == nullptr)
	{
#ifdef HOST_WS1470VM01
		Texture::FromFile(Device, "C:\\Users\\mrudder\\Downloads\\bg.png");
#endif

		float verts[] = 
		{ 
			0, 1, 0, 0.5, 1.0,
			-1, -1, 0, 0.0, 0.0,
			1, -1, 0, 1.0, 0.0
		};
		m_vertexBuffer = make_unique<VertexBuffer>(Device, sizeof(float) * 5, 3, verts, BufferUsage::Default);
	}

	if (m_indexBuffer == nullptr)
	{
		short indicies[] = { 0, 1, 2 };
		m_indexBuffer = make_unique<IndexBuffer>(Device, 3, BufferFormat::I16, indicies, BufferUsage::Default);
	}
}

void BufferTestSimulation::OnEndFrame()
{

}