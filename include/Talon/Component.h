
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Handle.h>
#include <unordered_map>

namespace Talon
{
	class Component;

	struct tagComponent { };
	typedef Handle<tagComponent> ComponentHandle;

	typedef u16 ComponentTypeId;
	
	typedef std::vector<ComponentHandle> ComponentList;
	typedef std::unordered_map<ComponentTypeId, ComponentList> ComponentChain;

	struct ComponentType
	{
		const char* ClassName;
		ComponentTypeId Id;
		std::function<Component*()> Creator;
		ComponentType* BaseClass;
	};

	class TalonApi Component
	{
	public:
		static inline ComponentType& GetType()
		{
			static ComponentType Type =
			{
				"Component",
				__s_typeId,
				nullptr,
				nullptr
			};

			return Type;
		}

		virtual ~Component();

		virtual void Create();
		virtual void Update();
		virtual void Destroy();

	private:
		static const ComponentTypeId __s_typeId = __COUNTER__;
	};

#define TALON_COMPONENT(comp, base) \
public: \
	static inline ComponentType& GetType() { static ComponentType Type = { #comp, __s_typeId, []{ return new comp(); }, &base::GetType() }; return Type; } \
private: \
	static const ComponentTypeId __s_typeId = __COUNTER__;
}