#pragma once

#include <Windows.h>

class CAddress
{
public:
	CAddress()
	{
		m_nValue = 0;
	}

	template<typename T>
	CAddress(const T& Val)
	{
		m_nValue = (uintptr_t)Val;
	}

	template<typename T = uintptr_t>
	T Get()
	{
		return (T)m_nValue;
	}

	CAddress& AddOffset(int nOffset)
	{
		if (m_nValue)
			m_nValue += nOffset;

		return *this;
	}

	CAddress& ToAbsolute(int nPreOffset, int nPostOffset)
	{
		if (m_nValue)
		{
			AddOffset(nPreOffset);
			m_nValue = m_nValue + sizeof(int) + *(int*)(m_nValue);
			AddOffset(nPostOffset);
		}

		return *this;
	}

	CAddress& Dereference(int nDereferences)
	{
		if (m_nValue)
			while (nDereferences-- != 0)
				m_nValue = *(uintptr_t*)(m_nValue);

		return *this;
	}

private:
	uintptr_t m_nValue;
};