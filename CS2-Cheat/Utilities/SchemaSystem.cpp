#include "SchemaSystem.h"

#include <cstdint>
#include <unordered_map>

#include "Interfaces.h"

using SchemaKeyValueMap_t = std::unordered_map<djb2_t, int16_t>;
using SchemaTableMap_t = std::unordered_map<uint32_t, SchemaKeyValueMap_t>;

static bool InitSchemaFieldsForClass(SchemaTableMap_t& tableMap, const char* className, uint32_t classKey) 
{
    CSchemaSystemTypeScope* pType = Interfaces::m_pSchemaSystem->FindTypeScopeForModule(CLIENT_DLL);
    if (!pType)
        return false;

    SchemaClassInfoData_t* pClassInfo = pType->FindDeclaredClass(className);
    if (!pClassInfo)
    {
        tableMap.emplace(classKey, SchemaKeyValueMap_t{});

        //LOG("InitSchemaFieldsForClass(): Class '%s' was not found!\n", className);
        return false;
    }

    short fieldsSize = pClassInfo->GetFieldsSize();
    SchemaClassFieldData_t* pFields = pClassInfo->GetFields();

    auto& keyValueMap = tableMap[classKey];
    keyValueMap.reserve(fieldsSize);

    for (int i = 0; i < fieldsSize; ++i) 
    {
        SchemaClassFieldData_t& field = pFields[i];

        //LOG("InitSchemaFieldsForClass(): %s::%s found at -> %x\n", className,
          //  field.m_name, field.m_offset);

        keyValueMap.emplace(djb2_hash(field.m_szName), field.m_nOffset);
    }

    //LOG("schemaTableMap[%s] has %llu fields.\n", className, keyValueMap.size());
    return true;
}

short SchemaSystem::GetOffset(const char* szClassName, djb2_t ClassKey, const char* szMemberName, djb2_t MemberKey)
{
      static SchemaTableMap_t schemaTableMap;
    const auto& tableMapIt = schemaTableMap.find(ClassKey);
    if (tableMapIt == schemaTableMap.cend()) {
        InitSchemaFieldsForClass(schemaTableMap, szClassName, ClassKey);
        return GetOffset(szClassName, ClassKey, szMemberName, MemberKey);
    }

    const SchemaKeyValueMap_t& tableMap = tableMapIt->second;
    if (tableMap.find(MemberKey) == tableMap.cend()) {
        //LOG("schema::GetOffset(): '%s' was not found in '%s'!\n", memberName,
          //  className);
        return 0;
    }

    return tableMap.at(MemberKey);
}