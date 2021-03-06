#pragma once

#include <stdint.h>

enum class CommandType : uint8_t
{
	Ping = 0,
	Error = 1,
	Disconnected = 2,
	Connect = 5,
	CreateParty = 6,
	Spawn = 10,
	Move = 11,
	Destroyed = 12,
	Fire = 13,
	Collision = 14
};

enum class ObjectType : uint8_t
{
	Ship = 0,
	Missile = 1,
	PowerUPs = 2,
	Obstacle = 3
};

enum class ShipType : uint8_t
{
	Standard = 0
};

enum class MissileType : uint8_t
{
	Standard = 0
};

enum class PowerUPsType : uint8_t
{
	Standard = 0
};

enum class ObstacleType : uint8_t
{
	Standard = 0
};

enum class GameStatus : uint8_t
{
	Waiting = 0,
	GameOver = 1,
	Win = 2
};

struct Ping
{
	CommandType cmdType;
	long time;
};

struct Error
{
	CommandType cmdType;
	uint8_t code;
};

struct Disconnected
{
	CommandType cmdType;
	uint8_t id;
};

struct Spawn
{
	CommandType cmdType;
	ObjectType object;
	uint8_t id_tospawn;
	uint32_t position;
	uint8_t type;
	uint8_t effect;
};

struct Move
{
	CommandType cmdType;
	uint8_t id_tomove;
	uint32_t position;
};

struct Fire
{
	CommandType cmdType;
	MissileType type;
	uint8_t id_launcher;
	uint32_t position;
	uint8_t velocity;
	uint8_t angle;
	uint8_t effect;
};

struct Collision
{
	CommandType cmdType;
	uint8_t id_first;
	uint8_t id_second;
};

struct Game
{
	CommandType cmdType;
	GameStatus status;
};

struct Level
{
	CommandType cmdType;
	uint8_t level;
};

#ifdef _MSC_VER

# define PACKED
#  pragma pack(push, 1)
#  pragma warning(disable : 4200)

struct Connect
{
	CommandType cmdType;
	uint16_t size;
	char data[0];
};

struct CreateParty
{
	CommandType cmdType;
	uint16_t size;
	char data[0];
};

#  pragma pack(pop)
# undef PACKED

#else

	struct Connect
	{
		CommandType cmdType;
		uint16_t size;
		char data[0];
	} __attribute__((packed));

	struct CreateParty
	{
		CommandType cmdType;
		uint16_t size;
		char data[0];
	} __attribute__((packed));

#endif