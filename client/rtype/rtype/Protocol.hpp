#pragma once

#include <stdint.h>

#define MAGIC_NUMBER 0x00ABCDEF
#define BAD_MAGIC "Error: bad magic number"

enum class PacketType : uint16_t
{
	PT_Error = 0,
	PT_Response = 1,
};

#ifdef _MSC_VER

# define PACKED
#  pragma pack(push, 1)
#  pragma warning(disable : 4200)

/* à revoir */
struct Packet
{
	unsigned int MAGIC;
	PacketType type;
	int size;
	char data[0];
};

#  pragma pack(pop)
# undef PACKED

#else

	struct Packet
	{
		unsigned int MAGIC;
		PacketType type;
		int size;
		char data[0];
	} __attribute__((packed));

#endif