#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <unordered_map>
#include <list>
#include <stdexcept>
#include <mutex>

#include "Timer.hpp"
#include "AEntity.hpp"

class World
{
public:
	static World TheWorld;
public:
	World(void);
	~World(void);

	void init(void);
	void update(float delta);
	void display(sf::RenderWindow &window);
	void recycle(void);

	template<typename T>
	T *spawnEntity(void)
	{
		T *entity = new T;

		try {
			entity->init();
		}
		catch (std::exception const& e) {
			delete (entity);
			throw (std::runtime_error(e.what()));
		}
		_mutex.lock();
		_entities.push_back(entity);
		_mutex.unlock();
		return (entity);
	}

private:
	std::list<AEntity *> _entities;
	std::mutex _mutex;
};