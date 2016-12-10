#pragma once

#include <stdint.h>

#include "CommandType.hpp"

#define RT_ERROR_NOT_FOUND 0x1
#define RT_ERROR_BAD_PASSWORD 0x2
#define RT_ERROR_ALREADY_EXIST 0x3

enum class ObjectType : uint8_t
{
	Ship = 0,
	Missile = 1,
	PowerUPs = 2,
	Obstacle = 3
};

enum class ShipType : uint8_t
{
	Standard = 0,
	ST_Boss = 1
};

enum class MissileType : uint8_t
{
	Standard = 0,
	MT_FriendFire_Lv1 = 1
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

enum class PowderType : uint8_t
{
	Standard = 0,
	LoadedPowder = 1
};

enum class CollisionType : uint8_t
{
	None = 0,
	Destruction = 1,
	PowerUP = 2
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
	uint16_t id;
};

struct Spawn
{
	CommandType cmdType;
	ObjectType object;
	uint16_t id_tospawn;
	uint32_t position;
	uint8_t type;
	uint8_t effect;
	bool is_player;
};

struct Move
{
	CommandType cmdType;
	uint16_t id_tomove;
	uint32_t position;
	uint16_t velocity;
	uint8_t direction;
};

struct Fire
{
	CommandType cmdType;
	MissileType type;
	uint16_t id;
	uint16_t id_launcher;
	uint32_t position;
	uint8_t velocity;
	uint8_t angle;
	uint8_t effect;
	uint8_t level;
};

struct Destroyed
{
	CommandType cmdType;
	uint16_t id;
};

struct Collision
{
	CommandType cmdType;
	CollisionType type;
	uint16_t id_first;
	uint16_t id_second;
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

struct Score
{
	CommandType cmdType;
	uint16_t id;
	uint16_t score;
};

struct Life
{
	CommandType cmdType;
	uint16_t id;
	uint8_t life;
};

struct LoadedPowder
{
	CommandType cmdType;
	uint16_t id;
	PowderType type;
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