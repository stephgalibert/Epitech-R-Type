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

#include "QuadTree.hpp"

class Player;

class World
{
public:
	static void init(Player **player, IClient *client);
	static void update(float delta);
	static void display(sf::RenderWindow &window);
	static void recycle(void);

	static AEntity *getEntityByID(uint16_t id);
	static Player *GetPlayer(void);

	template<typename T>
	static T *spawnEntity(void)
	{
		std::lock_guard<std::mutex> lock(Mutex);

		T *entity = new T;

		Entities.push_back(entity);
		return (entity);
	}

private:
	static std::list<AEntity *> Entities;
	static std::mutex Mutex;
	static IClient *Client;
	static Player **ThePlayer;
	static float Delta;
	static QuadTree *Region;
};