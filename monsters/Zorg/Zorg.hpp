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

	virtual void update(double delta);
	virtual void takeDamage(uint8_t damage);

	virtual void setID(uint16_t value);
	virtual void setPosition(uint16_t y);

	virtual uint16_t getID(void) const;
	virtual uint16_t getScoreValue(void) const;
	virtual uint8_t getHP(void) const;
	virtual uint8_t getFireRate(void) const;
	virtual uint16_t getVelocity(void) const;
	virtual uint8_t getAngle(void) const;
	virtual std::string getType(void) const;
	virtual uint16_t getPosition(void) const;
	virtual std::vector<std::pair<uint16_t, uint16_t> > const& getCanonRelativePosition(void) const;
	virtual std::vector<float> const& getCanonDegrees(void) const;

private:
	uint16_t _id;
	uint8_t _life;
	uint8_t _fireRate; // en seconde
	uint16_t _velocity;
	uint16_t _position; // que les Y vue que pour les X ça change pas (tout à droite de l'écran)
	uint8_t _angle; // angle de l'entité
	std::vector<std::pair<uint16_t, uint16_t> > _canonsRelativePosition; // positions des canons en relatif à l'entité
	std::vector<float> _canonsDegrees; // en degrée (ou radian ?)
};

extern "C" MONSTER_API IMonster *entry(void)
{
	return (new Zorg);
}

extern "C" MONSTER_API const char *type(void)
{
	return ("Zork");
}