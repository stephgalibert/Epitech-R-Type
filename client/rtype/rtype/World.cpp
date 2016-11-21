#include "World.hpp"

World::World(ProjectResource &resource)
	: _resource(resource)
{
}

World::~World(void)
{
	for (auto it : _entities) {
		it->recycle();
		delete (it);
	}
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
	window.clear();
	for (auto it : _entities) {
		window.draw(*it);
	}
	window.display();
}
