
#include "TalonPrefix.h"

#include <Talon/ComponentService.h>
#include <algorithm>

namespace Talon
{
	ComponentService::ComponentService()
	{
	}

	Component* ComponentService::CreateComponent(ComponentType& type, ComponentChain* chain)
	{
		TALON_ASSERT(chain);
		TALON_ASSERT(type.Creator);

		ComponentDatabase& db = m_components[type.Id];
		ComponentList& componentList = (*chain)[type.Id];

		// Need creator method so we can have the db create based on "type".
		ComponentHandle handle;
		ComponentEntry* entry = db.OpenHandle(handle);
		entry->Component = type.Creator();
		
		componentList.push_back(handle);

		return entry->Component;
	}

	Component* ComponentService::ResolveHandle(ComponentType& type, ComponentHandle handle)
	{
		ComponentDatabase& db = m_components[type.Id];
		return db.GetData(handle)->Component;
	}

	void ComponentService::ReleaseComponent(ComponentType& type, ComponentChain* chain, ComponentHandle handle)
	{
		ComponentDatabase& db = m_components[type.Id];
		ComponentList& componentList = (*chain)[type.Id];

		std::remove(std::begin(componentList), std::end(componentList), handle);
		db.CloseHandle(handle);
	}

	u32 ComponentService::GetComponentCount(ComponentType& type)
	{
		ComponentDatabase& db = m_components[type.Id];
		return db.GetUsedHandleCount();
	}

	void ComponentService::ForEach(ComponentType& type, ComponentChain* chain, std::function<void(Component*)> iterator)
	{
		ComponentDatabase& db = m_components[type.Id];

		if (chain)
		{
			for (ComponentHandle& handle : (*chain)[type.Id])
				iterator(db.GetData(handle)->Component);
		}
		else
		{
			db.ForEach([iterator](ComponentEntry* entry) { iterator(entry->Component); });
		}
	}
}