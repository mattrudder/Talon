
#pragma once

#include <Talon/TalonPublic.h>

namespace Talon
{
	class Component;

	typedef u16 ComponentTypeId;
	typedef std::vector<Component*>::iterator::distance_type ComponentHandle;

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
				[]{ TALON_ASSERT(false && "Cannot create abstract component class."); },
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