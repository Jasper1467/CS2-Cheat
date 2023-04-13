#include "Interfaces.h"

#include "CAddress.h"
#include <Windows.h>

typedef void* (*InstantiateInterfaceFn)();

struct InterfaceReg
{
	InstantiateInterfaceFn m_CreateFn;
	const char* m_pName;
	InterfaceReg* m_pNext;
};

template<typename T>
T FindInterface(const char* szModule, const char* szInterface)
{
	HMODULE hModule = GetModuleHandleA(szModule);
	if (!hModule)
		return nullptr;

	CAddress pCreateInterface = GetProcAddress(hModule, "CreateInterface");
	InterfaceReg* s_pInterfaceRegs = pCreateInterface.ToAbsolute(3, 0).Dereference(1).Get<InterfaceReg*>();
	void* rv = nullptr;

	for (; s_pInterfaceRegs;
		s_pInterfaceRegs = s_pInterfaceRegs->m_pNext) {
		if (strcmp(szInterface, s_pInterfaceRegs->m_pName) == 0) {
			rv = s_pInterfaceRegs->m_CreateFn();
			break;
		}
	}

	return reinterpret_cast<T>(rv);
}

void Interfaces::Initialize()
{
	m_pInput = FindInterface<void*>(CLIENT_DLL, "Source2Client002");
	m_pResourceService = FindInterface<CGameResourceService*>(ENGINE2_DLL, "GameResourceServiceClientV001");
	m_pSchemaSystem = FindInterface<CSchemaSystem*>(SCHEMASYSTEM_DLL, "SchemaSystem_001");

	m_pEntitySystem = m_pResourceService->GetGameEntitySystem();
}