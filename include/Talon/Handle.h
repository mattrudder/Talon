
#pragma once

#include <Talon/TalonPublic.h>

//http://scottbilas.com/publications/gem-resmgr/#l3
namespace Talon
{
	template <typename Tag, typename HandleType = u32>
	class Handle
	{
	public:
		Handle()
			: m_handle(0)
		{
		}

		void Initialize(HandleType index);

	private:
		static const u8 MaxIndexBits = sizeof(HandleType) / 2;
		static const u8 MaxMagicBits = sizeof(HandleType) / 2;
		static const HandleType MaxIndex = (1 << MaxIndexBits) - 1;
		static const HandleType MaxMagic = (1 << MaxMagicBits) - 1;

		union
		{
			struct
			{
				HandleType m_index : MaxIndexBits;
				HandleType m_magic : MaxMagicBits;
			};
			HandleType m_handle;
		};
	};

	template <typename Tag, typename HandleType>
	void Handle::Initialize(HandleType index)
	{
		TALON_ASSERT(IsNull());
		TALON_ASSERT(index <= MaxIndex);

		static std::atomic<HandleType> sAutoMagic = 0;
		
		if (++sAutoMagic > MaxMagic)
			sAutoMagic 
	}
}