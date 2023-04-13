#include "SigScanner.h"

SigScanner::Region_t SigScanner::GetRegionFromModule(HMODULE hModule)
{
	auto pDosHeader = (PIMAGE_DOS_HEADER)hModule;
	auto pNtHeader = (PIMAGE_NT_HEADERS)((uint8_t*)hModule + pDosHeader->e_lfanew);

	DWORD dwImageSize = pNtHeader->OptionalHeader.SizeOfImage;

	return Region_t((uint8_t*)hModule, dwImageSize);
}

std::vector<int> SigScanner::SignatureToBytes(const char* szSignature)
{
	std::vector<int> Bytes = {};
	char* Start = const_cast<char*>(szSignature);
	char* End = const_cast<char*>(szSignature) + strlen(szSignature);

	for (auto Current = Start; Current < End; ++Current)
	{
		if (*Current == '?')
		{
			++Current;

			if (*Current == '?')
				++Current;

			Bytes.push_back(-1);
		}
		else
			Bytes.push_back(strtoul(Current, &Current, 16));
	}

	return Bytes;
}

CAddress SigScanner::Scan(Region_t Region, std::vector<int> Signature)
{
	size_t s = Signature.size();
	const int* d = Signature.data();

	for (uintptr_t i = 0ul; i < Region.m_nSize - s; i++)
	{
		bool bFound = true;
		for (uintptr_t j = 0ul; j < s; j++)
		{
			if (Region.m_pBytes[i + j] != d[j] && d[j] != -1)
			{
				bFound = false;
				break;
			}
		}

		if (bFound)
			return CAddress(&Region.m_pBytes[i]);
	}

	return CAddress(nullptr);
}

CAddress SigScanner::Scan(Region_t Region, const char* szSignature)
{
	return Scan(Region, szSignature);
}

CAddress SigScanner::Scan(HMODULE hModule, const char* szSignature)
{
	return Scan(GetRegionFromModule(hModule), szSignature);
}