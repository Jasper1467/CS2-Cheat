#pragma once

#include <cstdint>

namespace Memory
{
	template <typename T = void*>
	inline constexpr T GetVFunc(void* thisptr, size_t nIndex)
	{
		return (*static_cast<T**>(thisptr))[nIndex];
	}

	template <typename T, typename ... Args_t>
	inline constexpr T CallVFunc(void* thisptr, size_t nIndex, Args_t... argList)
	{
		using VirtualFn = T(__thiscall*)(void*, decltype(argList)...);
		return (*static_cast<VirtualFn**>(thisptr))[nIndex](thisptr, argList...);
	}
}