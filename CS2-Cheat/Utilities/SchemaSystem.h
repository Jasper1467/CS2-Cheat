#pragma once

#include <memory>

#include "djb2.h"

#define SCHEMA_FIELD_OFFSET(varName, datatable, propName, extra_offset, type)  \
    std::add_lvalue_reference_t<type> varName() {                              \
        static constexpr auto datatable_hash = djb2_hash(datatable); \
        static constexpr auto prop_hash = djb2_hash(propName);       \
                                                                               \
        static const auto m_offset =                                           \
            SchemaSystem::GetOffset(datatable, datatable_hash, propName, prop_hash); \
                                                                               \
        return *reinterpret_cast<std::add_pointer_t<type>>(                    \
            (uintptr_t)(this) + m_offset + extra_offset);                      \
    }

#define SCHEMA_FIELD(varName, datatable, propName, type) \
    SCHEMA_FIELD_OFFSET(varName, datatable, propName, 0, type)

#define PSCHEMA_FIELD_OFFSET(varName, datatable, propName, extra_offset, type) \
    auto varName() {                                                           \
        static constexpr auto datatable_hash = djb2_hash(datatable); \
        static constexpr auto prop_hash = djb2_hash(propName);       \
                                                                               \
        static const auto m_offset =                                           \
            SchemaSystem::GetOffset(datatable, datatable_hash, propName, prop_hash); \
                                                                               \
        return reinterpret_cast<std::add_pointer_t<type>>(                     \
            (uintptr_t)(this) + m_offset + extra_offset);                      \
    }

#define PSCHEMA_FIELD(varName, datatable, propName, type) \
    PSCHEMA_FIELD_OFFSET(varName, datatable, propName, 0, type)

namespace SchemaSystem
{
	short GetOffset(const char* szClassName, djb2_t ClassKey, const char* szMemberName, djb2_t MemberKey);
}