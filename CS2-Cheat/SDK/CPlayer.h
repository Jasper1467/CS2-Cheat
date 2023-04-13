#pragma once

#include "CEntity.h"
#include <cstdint>

class CBasePlayerController : public C_BaseEntity
{
public:
	SCHEMA_FIELD(m_steamID, "CBasePlayerController", "m_steamID", uint64_t);
	SCHEMA_FIELD(m_hPawn, "CBasePlayerController", "m_hPawn", CHandle);
	SCHEMA_FIELD(m_bIsLocalPlayerController, "CBasePlayerController", "m_bIsLocalPlayerController", bool);
};

class CCSPlayerController : public CBasePlayerController
{
public:
	SCHEMA_FIELD(m_sSanitizedPlayerName, "CCSPlayerController", "m_sSanitizedPlayerName", const char*);
	SCHEMA_FIELD(m_iPawnHealth, "CCSPlayerController", "m_iPawnHealth", uint32_t);
	SCHEMA_FIELD(m_bPawnIsAlive, "CCSPlayerController", "m_bPawnIsAlive", bool);
};