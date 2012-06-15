
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

		Component* CreateComponent(ComponentType& type);
		void DestroyComponent(ComponentType& type, );

	private:
		std::unordered_map<ComponentTypeId, std::vector<Component*>> m_componentChain;
	};
}