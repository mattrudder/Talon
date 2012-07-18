#pragma once

#include <Talon/Simulation.h>

namespace Talon
{
	class Engine;

	class SpriteBatch;
	class Texture;
	
	class InputDevice;
	class GamepadInputDevice;
	class KeyboardInputDevice;
	class MouseInputDevice;

	class GameObject;
	class SpriteComponent;
}

class SandboxSimulation : public Talon::Simulation
{
public:
	SandboxSimulation(void);
	virtual ~SandboxSimulation(void);

protected:

	void Foo();

	void OnInitialized();
	void OnBeginFrame();
	void OnEndFrame();
	void OnShutdown();

private:
	std::unique_ptr<Talon::SpriteBatch> m_spriteBatch;
	std::shared_ptr<Talon::Texture> m_texture;

	Talon::Engine* m_engine;
	Talon::InputDevice* m_primaryDevice;
	Talon::GamepadInputDevice* m_gamepad;
	Talon::KeyboardInputDevice* m_keyboard;
	Talon::MouseInputDevice* m_mouse;

	Talon::GameObject* m_testGo;
	Talon::SpriteComponent* m_testSprite;
};

