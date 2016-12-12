#pragma once

#include <string>

#include "APC.hpp"
#include "LevelResource.hpp"
#include "Laser.hpp"
#include "Explosion.hpp"
#include "Powdered.hpp"
#include "LoadedPowdered.hpp"

#include "HUDController.hpp"

class IClient;

class Player : public APC
{
private:
	static const uint8_t FRAME_TOP;
	static const uint8_t FRAME_MID;
	static const uint8_t FRAME_BOT;
	static const uint8_t FRAME_EXP;

public:
	Player();
	virtual ~Player(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(void);

	virtual void collision(IClient *client, AEntity *other);
	virtual void applyCollision(CollisionType type);
	virtual void input(InputHandler &input);
	virtual void move(float delta);

	virtual void shoot(Fire const& param);

	virtual void respawn(void);

	void setIClient(IClient *client);
	void setHUD(HUDController *hud);

	/* ici les getters pour le hud */

private:
	void initFrame(void);
	void updateFrame(void);

	void keyboard(InputHandler &input);
	void joystick(InputHandler &input);

	void prepareShot(void);

	void collisionDestruction(void);
	void sendRespawnRequest(void);

	float _delta;
	float _deltaLastShoot;
	IClient *_client;
	HUDController *_hud;
	bool _decrease;
	uint8_t _targetFrame;
	uint8_t _currentFrame;

	std::unordered_map<uint8_t, sf::IntRect> _frames;
	uint8_t _currentDirection;
	std::pair<short, short> _resolution;

	Powdered *_powder;
	LoadedPowdered *_loadedPowder;
	bool _loadedShot;
	float _deltaLoadedShot;
};

