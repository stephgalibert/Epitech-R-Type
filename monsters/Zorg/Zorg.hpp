#pragma once

#ifdef WIN32
# define MONSTER_API __declspec(dllexport)
#else
# define MONSTERAPI
#endif

#include <iostream>
#include <vector>

#include "IMonster.hpp"

class Zorg : public IMonster
{
public:
	Zorg(void);
	virtual ~Zorg(void);

	virtual void update(float delta);
	virtual void takeDamage(uint8_t damage);

	virtual void setID(int value);

	virtual uint16_t getScoreValue(void) const;
	virtual uint8_t getHP(void) const;
	virtual uint8_t getFireRate(void) const;
	virtual uint16_t getSpeed(void) const;
	virtual ShipType getType(void) const;
	virtual uint16_t getSpawnPosition(void) const;
	virtual std::vector<std::pair<uint16_t, uint16_t> > const& getCanonRelativePosition(void) const;
	virtual std::vector<float> const& getCanonDegrees(void) const;

private:
	uint16_t _id;
	uint8_t _life;
	uint8_t _fireRate; // en seconde
	uint16_t _speed;
	uint16_t _spawnPosition; // que les Y vue que pour les X ça change pas (tout à droite de l'écran)
	std::vector<std::pair<uint16_t, uint16_t> > _canonsRelativePosition; // positions des canons en relatif
	std::vector<float> _canonsDegrees; // en degrée (ou radian ?)
};

extern "C" MONSTER_API IMonster *entry(void)
{
	return (new Zorg);
}