#pragma once

#include <stdint.h>

enum class CommandType : uint8_t
{
	Ping = 0,
	Error = 1,
	Disconnected = 2,
	GetParty = 3,
	GameStatus = 4,
	Connect = 5,
	CreateParty = 6,
	Score = 7,
	Respawn = 8,
	Message = 9,
	Spawn = 10,
	Move = 11,
	Destroyed = 12,
	Fire = 13,
	Collision = 14,
	LoadedPowder = 15
};