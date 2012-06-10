#include "SandboxSimulation.h"

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

#include <Talon/Graphics/SpriteBatch.h>

#include <windows.h>

using namespace std;
using namespace Talon;

SandboxSimulation::SandboxSimulation()
	: m_engine(Engine::Instance())
	, m_gamepad(nullptr)
	, m_keyboard(nullptr)
	, m_mouse(nullptr)
	, m_spriteBatch(nullptr)
	, m_texture(nullptr)
{
}

SandboxSimulation::~SandboxSimulation(void)
{
}

void SandboxSimulation::Foo()
{
	OutputDebugStringA("Button pressed!");
}

void SandboxSimulation::OnInitialized()
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

	m_texture = Texture::FromFile(Device, "test.png");
	m_spriteBatch = std::make_unique<SpriteBatch>(Device);
}

void SandboxSimulation::OnBeginFrame()
{
}

struct Card
{
	f32 x;
	f32 y;
	f32 xVel;
	f32 yVel;

	Card(f32 x = 0, f32 y = 0, f32 xVelocity = 0, f32 yVelocity = 0)
		: x(x)
		, y(y)
		, xVel(xVelocity)
		, yVel(yVelocity)
	{
	}

	void Update()
	{
		x += xVel;
		y += yVel;

		if (x + 128 > 1280)
		{
			x = 1280 - 128;
			xVel *= -1;
		}
		else if (x < 0)
		{
			x = 0;
			xVel *= -1;
		}

		if (y + 128 > 720)
		{
			y = 720 - 128;
			yVel *= -1;
		}
		else if (y < 0)
		{
			y = 0;
			yVel *= -1;
		}
	}
};

f32 randRange(int min, int max)
{
	return (f32)(min + (int)(rand() % ((max - min) + 1)));
}

void SandboxSimulation::OnEndFrame()
{
	m_spriteBatch->Begin();

	static const int count = 1000;
	static Card cards[count];
	static bool first = true;

	if (first)
	{
		srand(0);
		for (int i = 0; i < count; ++i)
		{
			cards[i].x = randRange(128, 1280 - 128);
			cards[i].y = randRange(128, 720 - 128);
			cards[i].xVel = randRange(4, 8);
			cards[i].yVel = randRange(3, 7);
		}
		first = false;
	}

	for (int i = 0; i < count; ++i)
	{
		cards[i].Update();
		m_spriteBatch->Draw(m_texture, cards[i].x, cards[i].y);
	}

	m_spriteBatch->End();
}