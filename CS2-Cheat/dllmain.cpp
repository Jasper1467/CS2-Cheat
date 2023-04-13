#include <Windows.h>

#include "Hooks/Hooks.h"
#include "Dependencies/ADVobfuscator/ObfuscatedCall.h"
#include "Utilities/Interfaces.h"

using namespace andrivet::ADVobfuscator::Machine1;

DWORD WINAPI OnDllAttach(LPVOID lpModule)
{
	//OBFUSCATED_CALL0(Interfaces::Initialize);
	//OBFUSCATED_CALL0(Hooks::Initialize);

	Interfaces::Initialize();
	Hooks::Initialize();

	return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		CreateThread(0, 0, OnDllAttach, hModule, 0, 0);

	return TRUE;
}

