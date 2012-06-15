

#include "TalonPrefix.h"
#include <Talon/GameObject.h>
#include <Talon/Component.h>

namespace Talon
{
	GameObject::GameObject()
	{

	}

	Component* GameObject::CreateComponent(ComponentType& type)
	{
		Component* component = type.Creator();
		m_componentChain.insert(std::make_pair(type.Id, component));

		return component;
	}
}