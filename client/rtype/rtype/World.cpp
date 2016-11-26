#include "World.hpp"

World World::TheWorld;

World::World(void)
{
}

World::~World(void)
{
	recycle();
}

void World::init(void)
{
}

void World::update(float delta)
{
	std::list<AEntity *>::iterator it = std::begin(_entities);

	while (it != std::end(_entities)) {
		if ((*it)->isWaitingForRecycle()) {
			(*it)->destroy();
			delete (*it);
			it = _entities.erase(it);
		}
		else {
			(*it)->update(delta);
			
			++it;
		}
	}
}

void World::display(sf::RenderWindow &window)
{
	for (auto it : _entities) {
		window.draw(*it);
	}
}

void World::recycle(void)
{
	for (auto it : _entities) {
		it->recycle();
		delete (it);
	}
	_entities.clear();
}