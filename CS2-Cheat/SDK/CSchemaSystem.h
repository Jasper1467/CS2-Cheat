#pragma once
#include <cstdint>

#include "../Utilities/Memory.h"

struct SchemaClassFieldData_t
{
	const char* m_szName;
	char pad0[0x8];
	short m_nOffset;
	char pad1[0xE];
};

class SchemaClassInfoData_t
{
public:
	const char* GetName()
	{
		return *reinterpret_cast<const char**>((uintptr_t)(this) + 0x8);
	}

	short GetFieldsSize()
	{
		return *reinterpret_cast<short*>((uintptr_t)(this) + 0x1C);
	}

	SchemaClassFieldData_t* GetFields()
	{
		return *reinterpret_cast<SchemaClassFieldData_t**>((uintptr_t)(this) + 0x28);
	}
};

class CSchemaSystemTypeScope
{
   public:
    SchemaClassInfoData_t* FindDeclaredClass(const char* szClass)
	{
        return Memory::CallVFunc<SchemaClassInfoData_t*>(this, 2, szClass);
    }
};

class CSchemaSystem 
{
   public:
    CSchemaSystemTypeScope* FindTypeScopeForModule(const char* szModule) 
	{
        return Memory::CallVFunc<CSchemaSystemTypeScope*>(this, 13, szModule);
    }
};