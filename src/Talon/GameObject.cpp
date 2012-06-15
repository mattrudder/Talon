

#include "TalonPrefix.h"
#include <Talon/GameObject.h>
#include <Talon/Component.h>
#include <Talon/ComponentService.h>
#include <Talon/Engine.h>

namespace Talon
{
	GameObject::GameObject()
	{

	}

	Component* GameObject::AddComponent(ComponentType& type)
	{
		return Engine::Instance()->GetComponentService()->CreateComponent(type, &m_componentChain);
	}

	void GameObject::RemoveComponent(ComponentType& type, ComponentHandle handle)
	{
		Engine::Instance()->GetComponentService()->ReleaseComponent(type, &m_componentChain, handle);
	}
}