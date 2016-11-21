#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <unordered_map>
#include <list>
#include <stdexcept>

#include "Timer.hpp"
#include "AEntity.hpp"

class World
{
public:
	World(ProjectResource &resource);
	~World(void);

	/* Init le monde */
	void init(void);

	/* Met à jour le monde */
	void update(float delta);

	/* Affiche le monde */
	void display(sf::RenderWindow &window);

	/* Retourne une entité T alloué et initialisé */
	template<typename T>
	AEntity *spawnEntity(void)
	{
		AEntity *entity = new T(_resource);

		try {
			entity->init();
		}
		catch (std::exception const& e) {
			delete (entity);
			throw (std::runtime_error(e.what()));
		}

		_entities.push_front(entity);

		return (entity);
	}

private:
	ProjectResource &_resource;
	std::list<AEntity *> _entities;
};