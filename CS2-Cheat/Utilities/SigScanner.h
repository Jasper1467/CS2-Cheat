#pragma once

#include <Windows.h>
#include <vector>
#include <array>
#include <cstdint>

#include "CAddress.h"

#define CLIENT_DLL ("client.dll")
#define ENGINE2_DLL ("engine2.dll")
#define SCHEMASYSTEM_DLL ("schemasystem.dll")

namespace SigScanner
{
	struct Region_t
	{
		Region_t(uint8_t* pBytes, size_t nSize) : m_pBytes(pBytes), m_nSize(nSize) {}

		bool operator==(Region_t& Other)
		{
			return (m_pBytes == Other.m_pBytes) && (m_nSize == Other.m_nSize);
		}

		uint8_t* m_pBytes;
		size_t m_nSize;
	};

	Region_t GetRegionFromModule(HMODULE hModule);

	
	std::vector<int> SignatureToBytes(const char* szSignature);

	CAddress Scan(Region_t Region, const std::vector<int> Signature);
	CAddress Scan(Region_t Region, const char* szSignature);
	CAddress Scan(HMODULE hModule, const char* szSignature);
}

#define SIGNATURE_SCAN(szmodule, signature) SigScanner::Scan(GetModuleHandleA(szmodule), signature)