
#pragma once

#include <Talon/TalonPublic.h>
#include <atomic>

// http://scottbilas.com/publications/gem-resmgr/#l3
namespace Talon
{
	template <typename Tag, typename HandleType = u32>
	class Handle
	{
	public:
		typedef HandleType IndexType;

		Handle()
			: m_handle(0)
		{
		}

		void Initialize(IndexType index);

		IndexType GetIndex() const { return m_data.Index; }
		IndexType GetMagic() const { return m_data.Magic; }
		IndexType GetHandle() const { return m_handle; }
		bool IsNull() const { return m_handle == 0; }

		operator IndexType() const { return m_handle; }

	private:
		static const IndexType MaxIndexBits = (sizeof(IndexType) * 8) / 2;
		static const IndexType MaxMagicBits = (sizeof(IndexType) * 8) / 2;
		static const IndexType MaxIndex = (1 << MaxIndexBits) - 1;
		static const IndexType MaxMagic = (1 << MaxMagicBits) - 1;

		union
		{
			struct
			{
				IndexType Index : MaxIndexBits;
				IndexType Magic : MaxMagicBits;
			} m_data;
			IndexType m_handle;
		};
	};

	template <typename Tag, typename IndexType>
	void Handle<Tag, IndexType>::Initialize(IndexType index)
	{
		IndexType mib = MaxIndexBits, mmb = MaxMagicBits, mi = MaxIndex, mm = MaxMagic;
		TALON_ASSERT(IsNull());
		TALON_ASSERT(index <= MaxIndex);
		TALON_ASSERT(mib && mmb && mi && mm);

		static std::atomic<IndexType> sAutoMagic;
		
		if (++sAutoMagic > MaxMagic)
			sAutoMagic = 1;

		m_data.Index = index;
		m_data.Magic = sAutoMagic;
	}

	template <typename Tag, typename IndexType>
	inline bool operator !=(Handle<Tag, IndexType> lhs, Handle<Tag, IndexType> rhs)
	{
		return lhs.GetHandle() != rhs.GetHandle();
	}

	template <typename Tag, typename IndexType>
	inline bool operator ==(Handle<Tag, IndexType> lhs, Handle<Tag, IndexType> rhs)
	{
		return lhs.GetHandle() == rhs.GetHandle();
	}
}