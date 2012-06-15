
#pragma once

#include <Talon/TalonPublic.h>

namespace Talon
{
	template <typename Data, typename HandleType>
	class HandleDatabase
	{
	public:
		HandleDatabase() { }
		~HandleDatabase() { }

		Data* OpenHandle(HandleType& handle, std::function<Data()> creator = nullptr);
		void CloseHandle(HandleType handle);

		Data* GetData(HandleType handle);
		const Data* GetData(HandleType handle) const;

		void ForEach(std::function<void(Data*)> iterator);

		u32 GetUsedHandleCount() const
		{
			return m_magicNumbers.size() - m_freeList.size();
		}

		bool HasUsedHandles() const
		{
			return !!GetUsedHandleCount();
		}

	private:
		Data* GetDataCore(HandleType handle);

		typedef typename HandleType::IndexType IndexType;

		typedef std::vector<Data> UserContainer;
		typedef std::vector<IndexType> MagicContainer;
		typedef std::vector<IndexType> FreeContainer;

		UserContainer m_userData;
		MagicContainer m_magicNumbers;
		FreeContainer m_freeList;
	};

	template <typename Data, typename HandleType>
	Data* HandleDatabase<Data, HandleType>::OpenHandle(HandleType& handle, std::function<Data()> creator)
	{
		IndexType index;
		if (m_freeList.empty())
		{
			index = m_magicNumbers.size();
			handle.Initialize(index);
			m_userData.push_back(creator ? creator() : Data());
			m_magicNumbers.push_back(handle.GetMagic());
		}
		else
		{
			index = m_freeList.back();
			handle.Initialize(index);
			m_freeList.pop_back();
			m_magicNumbers[index] = handle.GetMagic();
		}

		// Dereference iterator, and get the address of the actual data.
		auto location = m_userData.begin() + index;
		return &(*location);
	}

	template <typename Data, typename HandleType>
	void HandleDatabase<Data, HandleType>::CloseHandle(HandleType handle)
	{
		IndexType index = handle.GetIndex();

		TALON_ASSERT(index < m_userData.size());
		TALON_ASSERT(m_magicNumbers[index] == handle.GetMagic());

		m_magicNumbers[index] = 0;
		m_freeList.push_back(index);
	}

	template <typename Data, typename HandleType>
	Data* HandleDatabase<Data, HandleType>::GetData(HandleType handle)
	{
		if (handle.IsNull())
			return nullptr;

		IndexType index = handle.GetIndex();
		if (index >= m_userData.size() || m_magicNumbers[index] != handle.GetMagic())
		{
			TALON_ASSERT(false && "Dereferenced an invalid handle.");
			return nullptr;
		}

		// Dereference iterator, and get the address of the actual data.
		auto location = m_userData.begin() + index;
		return &(*location);
	}

	template <typename Data, typename HandleType>
	const Data* HandleDatabase<Data, HandleType>::GetData(HandleType handle) const
	{
		typedef HandleDatabase<Data, HandleType> ThisType;
		return const_cast<ThisType*>(this)->GetData(handle);
	}

	template <typename Data, typename HandleType>
	void HandleDatabase<Data, HandleType>::ForEach(std::function<void(Data*)> iterator)
	{
		UserContainer::iterator location = begin(m_userData);
		for (u32 i = 0; i < m_magicNumbers.size(); ++i)
		{
			if (m_magicNumbers[i] != 0)
				iterator(&(*location));

			++location;
		}
	}
}