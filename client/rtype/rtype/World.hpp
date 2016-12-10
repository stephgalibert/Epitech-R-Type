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
	static void init(IClient *client);
	static void update(float delta);
	static void display(sf::RenderWindow &window);
	static void recycle(void);

	static AEntity *getEntityByID(uint8_t id);

	template<typename T>
	static T *spawnEntity(void)
	{
		std::lock_guard<std::mutex> lock(Mutex);

		T *entity = new T;

		Entities.push_back(entity);
		return (entity);
	}

	static void pushEntity(AEntity *entity)
	{
		std::lock_guard<std::mutex> lock(Mutex);
		Entities.push_back(entity);
	}

private:
	static std::list<AEntity *> Entities;
	static std::vector<AEntity *> ToPush;
	static std::mutex Mutex;
	static IClient *Client;
	static Player **thePlayer;
	static float Delta;
};