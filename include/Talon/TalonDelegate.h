
#pragma once
#include <Talon/TalonPublic.h>
#include <functional>
#include <vector>

namespace Talon
{
	/** Defines a multicast delegate container, which can only be invoked from the owning class. */
	template <typename Owner, typename F>
	class delegate 
	{
	public:
		explicit delegate() { }

		template<typename F2>
		delegate(std::function<F2> fn)
		{
			m_listeners.push_back(fn);
		}

		void Add(std::function<F> fn)
		{
			m_listeners.push_back(fn);
		}

		void Clear()
		{
			m_listeners.clear();
		}

		void operator+=(std::function<F> fn) 
		{
			Add(fn);
		}

		bool Empty() const
		{
			return m_listeners.empty();
		}

		operator bool() const
		{
			return m_listeners.empty();
		}

	private:
		friend Owner;

		void operator()() const
		{
			for (auto i = m_listeners.begin(); i != m_listeners.end(); ++i)
				(*i)();
		}

		template<typename T0>
		void operator()(T0&& t0) const
		{
			for (auto i = m_listeners.begin(); i != m_listeners.end(); ++i)
				(*i)(t0);
		}

		template<typename T0, typename T1>
		void operator()(T0&& t0, T1&& t1) const
		{
			for (auto i = m_listeners.begin(); i != m_listeners.end(); ++i)
				(*i)(t0, t1);
		}

		template<typename T0, typename T1, typename T2>
		void operator()(T0&& t0, T1&& t1, T2&& t2) const
		{
			for (auto i = m_listeners.begin(); i != m_listeners.end(); ++i)
				(*i)(t0, t1, t2);
		}

		template<typename T0, typename T1, typename T2, typename T3>
		void operator()(T0&& t0, T1&& t1, T2&& t2, T3&& t3) const
		{
			for (auto i = m_listeners.begin(); i != m_listeners.end(); ++i)
				(*i)(t0, t1, t2, t3);
		}

		template<typename T0, typename T1, typename T2, typename T3, typename T4>
		void operator()(T0&& t0, T1&& t1, T2&& t2, T3&& t3, T4&& t4) const
		{
			for (auto i = m_listeners.begin(); i != m_listeners.end(); ++i)
				(*i)(t0, t1, t2, t3, t4);
		}

		template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		void operator()(T0&& t0, T1&& t1, T2&& t2, T3&& t3, T4&& t4, T5&& t5) const
		{
			for (auto i = m_listeners.begin(); i != m_listeners.end(); ++i)
				(*i)(t0, t1, t2, t3, t4, t5);
		}

		template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		void operator()(T0&& t0, T1&& t1, T2&& t2, T3&& t3, T4&& t4, T5&& t5, T6&& t6) const
		{
			for (auto i = m_listeners.begin(); i != m_listeners.end(); ++i)
				(*i)(t0, t1, t2, t3, t4, t5, t6);
		}

		template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		void operator()(T0&& t0, T1&& t1, T2&& t2, T3&& t3, T4&& t4, T5&& t5, T6&& t6, T7&& t7) const
		{
			for (auto i = m_listeners.begin(); i != m_listeners.end(); ++i)
				(*i)(t0, t1, t2, t3, t4, t5, t6, t7);
		}

		template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		void operator()(T0&& t0, T1&& t1, T2&& t2, T3&& t3, T4&& t4, T5&& t5, T6&& t6, T7&& t7, T8&& t8) const
		{
			for (auto i = m_listeners.begin(); i != m_listeners.end(); ++i)
				(*i)(t0, t1, t2, t3, t4, t5, t6, t7, t8);
		}

		template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		void operator()(T0&& t0, T1&& t1, T2&& t2, T3&& t3, T4&& t4, T5&& t5, T6&& t6, T7&& t7, T8&& t8, T9&& t9) const
		{
			for (auto i = m_listeners.begin(); i != m_listeners.end(); ++i)
				(*i)(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9);
		}

	private:
		std::vector<std::function<F>> m_listeners;
	};
}