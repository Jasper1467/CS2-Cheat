#pragma once

using djb2_t = unsigned long;
djb2_t djb2_hash(unsigned char* str)
{
	unsigned long a = 5381;

	int c;
	while (c = *str++)
		a = ((a << 5) + a) + c;

	return a;
}

djb2_t djb2_hash(const char* str)
{
	unsigned long a = 5381;

	int c;
	while (c = *str++)
		a = ((a << 5) + a) + c;

	return a;
}