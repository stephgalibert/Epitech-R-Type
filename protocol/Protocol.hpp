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
	Laser = 1,
	DoubleLaser = 2,
	FireBall = 3,
	RedMissile = 4
};

enum class PowerUPsType : uint8_t
{
	Standard = 0,
	IncreaseNumberOfCanon = 1
};

enum class ObstacleType : uint8_t
{
	Standard = 0
};

enum class GameStatusType : uint8_t
{
	None = 0,
	Waiting = 1,
	Playing = 2,
	GameOver = 3,
	GameWin = 4,
	BossIncoming = 5
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

enum class EffectType : uint8_t
{
	None = 0,
	ScoreX2 = 1
};

struct Effect
{
	CommandType cmdType;
	EffectType type;
	uint16_t id;
	bool to_add;
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

struct SpawnPowerUp
{
	CommandType cmdType;
	PowerUPsType type;
	uint16_t id;
	uint32_t position;
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
	float angle;
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

struct Respawn
{
	CommandType cmdType;
	uint32_t position;
	uint16_t id;
	uint8_t life;
};

struct GameStatus
{
	CommandType cmdType;
	GameStatusType status;
};

struct Disconnect
{
	CommandType cmdType;
};

#ifdef _MSC_VER

# define PACKED
#  pragma pack(push, 1)
#  pragma warning(disable : 4200)

struct Connect
{
	CommandType cmdType;
	uint32_t size;
	char data[0];
};

struct CreateParty
{
	CommandType cmdType;
	uint16_t size;
	char data[0];
};

struct GetParty
{
	CommandType cmdType;
	uint8_t nbPlayer;
	bool pwdPresent;
	bool running;
	uint8_t size;
	char data[0];
};

struct Message
{
	CommandType cmdType;
	uint16_t size;
	char data[0];
};

struct SpawnPlayer
{
	CommandType cmdType;
	uint16_t id;
	uint32_t position;
	uint8_t health;
	bool isPlayer;
	uint8_t size;
	char username[0];
};

struct SpawnMonster
{
	CommandType cmdType;
	uint16_t id;
	uint32_t position;
	uint8_t health;
	uint16_t velocity;
	uint8_t angle;
	uint16_t size;
	char type[0];
};

#  pragma pack(pop)
# undef PACKED

#else

	struct Connect
	{
		CommandType cmdType;
		uint32_t size;
		char data[0];
	} __attribute__((packed));

	struct CreateParty
	{
		CommandType cmdType;
		uint16_t size;
		char data[0];
	} __attribute__((packed));

	struct GetParty
	{
		CommandType cmdType;
		uint8_t nbPlayer;
		bool pwdPresent;
		bool running;
		uint8_t size;
	  	char data[0];
	} __attribute__((packed));

	struct Message
	{
		CommandType cmdType;
		uint16_t size;
		char data[0];
	} __attribute__((packed));

	struct SpawnPlayer
	{
		CommandType cmdType;
		uint16_t id;
		uint32_t position;
		uint8_t health;
		bool isPlayer;
		uint8_t size;
		char username[0];
	} __attribute__((packed));

	struct SpawnMonster
	{
		CommandType cmdType;
		uint16_t id;
		uint32_t position;
		uint8_t health;
		uint16_t velocity;
		uint8_t angle;
		uint16_t size;
		char type[0];
	} __attribute__((packed));

#endif
