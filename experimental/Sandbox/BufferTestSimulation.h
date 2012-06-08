#pragma once

#include <Talon/Simulation.h>

namespace Talon
{
	class Engine;
	class IndexBuffer;
	class InputDevice;
	class VertexBuffer;
	class Texture;

	class GamepadInputDevice;
	class KeyboardInputDevice;
	class MouseInputDevice;
	class SpriteBatch;
}

class BufferTestSimulation : public Talon::Simulation
{
public:
	BufferTestSimulation(void);
	virtual ~BufferTestSimulation(void);

protected:

	void Foo();

	void OnInitialized();
	void OnBeginFrame();
	void OnEndFrame();

private:
	std::unique_ptr<Talon::VertexBuffer> m_vertexBuffer;
	std::unique_ptr<Talon::IndexBuffer> m_indexBuffer;
	std::unique_ptr<Talon::SpriteBatch> m_spriteBatch;
	std::shared_ptr<Talon::Texture> m_texture;

	Talon::Engine* m_engine;
	Talon::InputDevice* m_primaryDevice;
	Talon::GamepadInputDevice* m_gamepad;
	Talon::KeyboardInputDevice* m_keyboard;
	Talon::MouseInputDevice* m_mouse;
};

