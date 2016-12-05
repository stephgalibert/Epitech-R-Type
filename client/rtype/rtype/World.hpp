#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <unordered_map>
#include <list>
#include <stdexcept>
#include <mutex>

#include "Timer.hpp"
#include "AEntity.hpp"

#include "IClient.hpp"

class Player;

class World
{
public:
	static World TheWorld;
public:
	World(void);
	~World(void);

	void init(IClient *client, Player **player);
	void update(float delta);
	void display(sf::RenderWindow &window);
	void recycle(void);

	AEntity *getEntityByID(uint8_t id) const;

	template<typename T>
	T *spawnEntity(void)
	{
		T *entity = new T;

		_entities.push_back(entity);
		return (entity);
	}

private:
	std::list<AEntity *> _entities;
	std::vector<AEntity *> _toPush;
	std::mutex _mutex;
	IClient *_client;
	Player **_player;
	float _delta;
};