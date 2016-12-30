#pragma once

#include <utility>
#include <stdint.h>
#include <vector>
#include <set>

#include "Protocol.hpp"
#include "PlayerData.hpp"

#define EAST 1
#define WEAST 2
#define NORTH 4
#define SOUTH 8

class IMonster
{
public:
	enum class State : uint8_t
	{
		None = 0,
		Fire = 1,
		Move = 2
	};

public:
	virtual ~IMonster(void) {}

	virtual void update(double delta, std::vector<PlayerData> const& players) = 0;
	virtual void takeDamage(uint8_t damage) = 0;

	virtual void setID(uint16_t value) = 0;
	virtual void setPosition(std::pair<double, double> const& pos) = 0;
	virtual void setAngle(double angle) = 0;
	virtual void move(double x, double y) = 0;

	virtual State popAction(void) = 0;

	virtual uint16_t getID(void) const = 0;
	virtual int getDirection(void) const = 0;
	virtual uint16_t getScoreValue(void) const = 0;
	virtual uint8_t getHP(void) const = 0;
	virtual double getFireRate(void) const = 0;
	virtual uint16_t getVelocity(void) const = 0;
	virtual uint8_t getAngle(void) const = 0;
	virtual std::string getType(void) const = 0;
	virtual std::pair<double, double> const& getPosition(void) const = 0; // ?
	virtual std::vector<std::pair<uint16_t, uint16_t> > const& getCanonRelativePosition(void) const = 0;
	virtual std::vector<float> const& getCanonDegrees(void) const = 0;
	virtual std::vector<uint8_t> const& getCanonVelocity(void) const = 0;
};