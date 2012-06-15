
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Component.h>

#include <unordered_map>


namespace Talon
{
	class TalonApi GameObject
	{
	public:
		GameObject();

		Component* AddComponent(ComponentType& type);
		void RemoveComponent(ComponentType& type, ComponentHandle handle);

	private:
		ComponentChain m_componentChain;
	};
}