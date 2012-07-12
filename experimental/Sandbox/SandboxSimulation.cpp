#include "SandboxSimulation.h"

#include <Talon/Engine.h>
#include <Talon/ComponentService.h>
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

#include <Talon/GameObject.h>
#include <Talon/Graphics/SpriteComponent.h>

using namespace std;
using namespace Talon;

//float randRange(int min, int max)
//{
//	return (float)(min + (int)(rand() % ((max - min) + 1)));
//}

float randRange(float min, int max)
{
	return min + (float)rand()/((float)RAND_MAX/(max-min));
}

SandboxSimulation::SandboxSimulation()
    : m_spriteBatch(nullptr)
    , m_texture(nullptr)
    , m_engine(Engine::Instance())
	, m_gamepad(nullptr)
	, m_keyboard(nullptr)
	, m_mouse(nullptr)
{
}

SandboxSimulation::~SandboxSimulation(void)
{
}

void SandboxSimulation::Foo()
{
//	OutputDebugStringA("Button pressed!");
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

	m_texture = Texture::FromFile(Device, "test_alpha.png");
	m_spriteBatch = std::make_unique<SpriteBatch>(Device);

	m_testGo = new GameObject();
	m_testSprite = (SpriteComponent*) m_testGo->AddComponent(SpriteComponent::GetType());
	if (m_testSprite)
	{
		m_testSprite->SetPosition(float2(randRange(128, 1280 - 128), randRange(128, 720 - 128)));
		m_testSprite->SetSourceBounds(float4(randRange(4, 8), randRange(3, 7), 0, 0));
		m_testSprite->SetTexture(m_texture);
		m_testSprite->SetColor(float4(1, 1, 1, 0.5));
	}
}

void SandboxSimulation::OnBeginFrame()
{
}

struct Card
{
	float x;
	float y;
	float xVel;
	float yVel;
	GameObject go;

	Card(float x = 0, float y = 0, float xVelocity = 0, float yVelocity = 0)
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

void SandboxSimulation::OnEndFrame()
{
#if TALON_MAC
	return;
#endif
	
	m_spriteBatch->Begin();

	static const int count = 10;
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

			//SpriteComponent* sprite = (SpriteComponent*) cards[i].go.AddComponent(SpriteComponent::GetType());
			//if (sprite)
			//{
			//	sprite->SetOrigin(float2(randRange(128, 1280 - 128), randRange(128, 720 - 128)));
			//	sprite->SetSourceBounds(float4(randRange(4, 8), randRange(3, 7), 0, 0));
			//	sprite->SetTexture(m_texture);
			//}
		}
		first = false;
	}
	
	float spriteAccel = 10 + max(m_gamepad->GetAxis(InputDeviceAxis::RightZ), m_gamepad->GetAxis(InputDeviceAxis::LeftZ)) * 10;
	float2 spritePos = m_testSprite->GetPosition();
	float2 spriteControl(m_gamepad->GetAxis(InputDeviceAxis::LeftX) - 0.5f, m_gamepad->GetAxis(InputDeviceAxis::LeftY) - 0.5f);
	spritePos.x += spriteControl.x * spriteAccel;
	spritePos.y -= spriteControl.y * spriteAccel;
	m_testSprite->SetPosition(spritePos);

	/*for (int i = 0; i < count; ++i)
	{
	cards[i].Update();
	m_spriteBatch->Draw(m_texture, cards[i].x, cards[i].y, 64, 64);
	}*/

	Engine::Instance()->GetComponentService()->ForEach(SpriteComponent::GetType(), nullptr, [this](Component* component)
	{
		SpriteComponent* sprite = (SpriteComponent*) component;
		float2 spritePos = sprite->GetPosition();
		m_spriteBatch->Draw(sprite->GetTexture(), spritePos.x, spritePos.y, (float)sprite->GetTexture()->GetWidth(), (float)sprite->GetTexture()->GetHeight(), float4(randRange(0, 1), randRange(0, 1), randRange(0, 1), 1));
	});

	m_spriteBatch->End();
}