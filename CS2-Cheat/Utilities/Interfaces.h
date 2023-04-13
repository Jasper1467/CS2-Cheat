#pragma once

#include "../SDK/CGameResourceService.h"
#include "../SDK/CGameEntitySystem.h"
#include "../SDK/CSchemaSystem.h"

namespace Interfaces
{
	void Initialize();

	inline void* m_pInput = nullptr;
	inline CGameResourceService* m_pResourceService = nullptr;
	inline CGameEntitySystem* m_pEntitySystem = nullptr;
	inline CSchemaSystem* m_pSchemaSystem = nullptr;
}