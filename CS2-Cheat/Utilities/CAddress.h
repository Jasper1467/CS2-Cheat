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

	CAddress& ToAbsolute(int nPreOffset = 0, int nPostOffset = 0)
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

	CAddress& ResolveRip(uintptr_t nRvaOffset, uintptr_t nRipOffset)
	{
		if (m_nValue || nRvaOffset || nRipOffset)
		{
			uintptr_t rva = m_nValue + nRvaOffset;
			uintptr_t rip = m_nValue + nRipOffset;

			m_nValue = uintptr_t(rva + rip);
			return *this;
		}
	}

private:
	uintptr_t m_nValue;
};