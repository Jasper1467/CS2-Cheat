#pragma once

// https://github.com/papstuc/counterstrike2/blob/main/counterstrike2/counterstrike2/source2-sdk/interfaces/i_schema_system.hpp

#include <cstdint>
#include <array>
#include <vector>

class CUtlMemoryPool
{
public:
	std::int32_t BlockSize()
	{
		return this->m_blocks_per_blob;
	}

	std::int32_t Count()
	{
		return this->m_block_allocated_size;
	}

	std::int32_t PeakCount()
	{
		return this->m_peak_alloc;
	}

private:
	std::int32_t m_block_size = 0;
	std::int32_t m_blocks_per_blob = 0;
	std::int32_t m_grow_mode = 0;
	std::int32_t m_blocks_allocated = 0;
	std::int32_t m_block_allocated_size = 0;
	std::int32_t m_peak_alloc = 0;
};

template<class T, class key_type = std::uint64_t>
class CUtlTSHash
{
public:
	static std::uint64_t InvalidHandle()
	{
		return static_cast<std::uint64_t>(0);
	}

	std::int32_t BlockSize()
	{
		return this->m_entry_memory.BlockSize();
	}

	std::int32_t Count()
	{
		return this->m_entry_memory.Count();
	}

	std::vector<T> GetElements()
	{
		std::vector<T> list;

		std::int32_t n_count = this->Count();
		std::int32_t n_index = 0;
		hash_unallocated_data_t* unallocated_data = this->m_buckets.m_unallocated_data;
		for (hash_unallocated_data_t* element = unallocated_data; element; element = element->m_next)
		{
			for (std::int32_t i = 0; i < this->BlockSize() && i != n_count; i++)
			{
				list.emplace_back(element->m_current_block_list.at(i).m_data);
				n_index++;

				if (n_index >= n_count)
				{
					break;
				}
			}
		}
		return list;
	}

public:
	template<typename dataT>
	struct hash_fixed_data_internal_t
	{
		key_type m_ui_key;
		hash_fixed_data_internal_t<dataT>* m_next;
		dataT m_data;
	};

	using hash_fixed_data_t = hash_fixed_data_internal_t< T >;

	template< typename dataT >
	struct hash_fixed_struct_data_internal_t
	{
		dataT m_data;
		key_type m_ui_key;
	};

	using hash_fixed_struct_data = hash_fixed_struct_data_internal_t<T>;

	struct hash_struct_data_t
	{
		char pad_1[0x10];
		std::array<hash_fixed_struct_data, 256> m_list;
	};

	struct hash_allocated_data_t
	{
	public:
		std::array<hash_fixed_data_t, 128> get_list()
		{
			return this->m_list;
		}

	private:
		char pad_1[0x18];
		std::array<hash_fixed_data_t, 128> m_list;
	};

	template<typename dataT>
	struct hash_bucket_data_internal_t
	{
		dataT m_data;
		hash_fixed_data_internal_t<dataT>* m_next;
		key_type m_ui_key;
	};

	using hash_bucket_data_t = hash_bucket_data_internal_t<T>;

	struct hash_unallocated_data_t
	{
		hash_unallocated_data_t* m_next = nullptr;
		key_type m_6114;
		key_type m_ui_key;
		key_type m_i_unk_1;
		std::array<hash_bucket_data_t, 256> m_current_block_list;
	};

	struct hash_bucket_t
	{
		hash_struct_data_t* m_struct_data = nullptr;
		void* m_mutex_list = nullptr;
		hash_allocated_data_t* m_allocated_data = nullptr;
		hash_unallocated_data_t* m_unallocated_data = nullptr;
	};

	CUtlMemoryPool m_entry_memory;
	hash_bucket_t m_buckets;
	bool m_needs_commit = false;
};