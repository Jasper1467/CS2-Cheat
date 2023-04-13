#pragma once

#include "../Utilities/djb2.h"
#include "../Utilities/Memory.h"
#include "../Utilities/SchemaSystem.h"

#include "Vectors.h"
#include "CHandle.h"
#include "CSchemaSystem.h"

class CEntityIdentity
{
public:
	SCHEMA_FIELD(m_designerName, "CEntityIdentity", "m_designerName", const char*);
};

class CEntityInstance
{
public:
	SchemaClassInfoData_t* Schema_DynamicBinding()
	{
		return Memory::CallVFunc<SchemaClassInfoData_t*>(this, 0);
	}

	CHandle GetRefEHandle()
	{
		CHandle handle;
		Memory::CallVFunc<void*>(this, 2, &handle);
		return handle;
	}

	SCHEMA_FIELD(m_pEntity, "CEntityInstance", "m_pEntity", CEntityIdentity*);
};

class CGameSceneNode
{
public:
	SCHEMA_FIELD(m_vecAbsOrigin, "CGameSceneNode", "m_vecAbsOrigin", Vector);
};

class C_BaseEntity : public CEntityInstance
{
public:
	bool IsPlayerController()
	{
		CEntityIdentity* pIdentity = m_pEntity();
		if (!pIdentity) return false;

		const char* designerName = pIdentity->m_designerName();
		if (!designerName) return false;

		static constexpr auto cs_player_controller = djb2_hash("cs_player_controller");
		return djb2_hash(designerName) == cs_player_controller;
	}

	SCHEMA_FIELD(m_pGameSceneNode, "C_BaseEntity", "m_pGameSceneNode", CGameSceneNode*);
};