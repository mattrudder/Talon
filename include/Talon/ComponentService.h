
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Component.h>
#include <Talon/HandleDatabase.h>

#include <unordered_map>

namespace Talon
{
	class TalonApi ComponentService
	{
	public:
		ComponentService();

		Component* CreateComponent(ComponentType& type, ComponentChain* chain);
		Component* ResolveHandle(ComponentType& type, ComponentHandle handle);
		void ReleaseComponent(ComponentType& type, ComponentChain* chain, ComponentHandle handle);

		u32 GetComponentCount(ComponentType& type);

		void ForEach(ComponentType& type, ComponentChain* chain, std::function<void(Component*)> iterator);

	private:
		struct ComponentEntry
		{
			Component* Component;
		};

		typedef HandleDatabase<ComponentEntry, ComponentHandle> ComponentDatabase;
		typedef std::unordered_map<ComponentTypeId, ComponentDatabase> ComponentPool;

		ComponentPool m_components;
	};
}