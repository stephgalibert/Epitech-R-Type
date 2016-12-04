#include "World.hpp"
#include "Player.hpp"

World World::TheWorld;

World::World(void)
	: _client(NULL),
	  _player(NULL)
{
	_delta = 0;
}

World::~World(void)
{
	recycle();
}

void World::init(IClient *client, Player **player)
{
	_client = client;
	_player = player;
}

void World::update(float delta)
{
	std::lock_guard<std::mutex> lock(_mutex);
	std::list<AEntity *>::iterator it = std::begin(_entities);

	while (it != std::end(_entities)) {
		if ((*it)->isWaitingForRecycle()) {
			(*it)->destroy();
			if (*_player != NULL && (*_player == (*it))) {
				delete (*_player);
				*_player = NULL;
			}
			else {
				delete (*it);
			}
			it = _entities.erase(it);
		}
		else if (!(*it)->isInitialized()) {
			(*it)->init();
			++it;
		}
		else {
			(*it)->update(delta);
			
			for (auto it_sub : _entities) {
				if (it_sub->getID() != (*it)->getID() && it_sub->isCollidingWith(*it)) {
					it_sub->collision(_client, (*it));
				}
			}

			++it;
		}
	}

	//for (auto it : _toPush) {
	//	_entities.push_back(it);
	//}
	//_toPush.clear();

	//_delta += delta;
	//if (_delta > 0.5 && _entities.size() > 1) {
	//	Explosion *explosion = World::TheWorld.spawnEntity<Explosion>();
	//	explosion->setPosition((*_entities.begin())->getPosition());
	//	_delta = 0;
	//}
}

void World::display(sf::RenderWindow &window)
{
	std::lock_guard<std::mutex> lock(_mutex);

	for (auto it : _entities) {
		window.draw(*it);
	}
}

void World::recycle(void)
{
	std::lock_guard<std::mutex> lock(_mutex);

	for (auto it : _entities) {
		it->recycle();
		delete (it);
	}
	_entities.clear();
}

AEntity *World::getEntityByID(uint8_t id) const
{
	for (auto it : _entities) {
		if (it->getID() == id) {
			return (it);
		}
	}
	return (NULL);
}