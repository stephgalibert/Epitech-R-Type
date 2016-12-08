#include "World.hpp"

std::list<AEntity *> World::Entities;
std::vector<AEntity *> World::ToPush;
std::mutex World::Mutex;
IClient *World::Client;

void World::init(IClient *client)
{
	Client = client;
}

void World::update(float delta)
{
	std::lock_guard<std::mutex> lock(Mutex);
	std::list<AEntity *>::iterator it = std::begin(Entities);

	while (it != std::end(Entities)) {
		if ((*it)->isWaitingForRecycle()) {
			(*it)->destroy();
			delete (*it);
			it = Entities.erase(it);
		}
		else if ((*it)->isReadyForInit()) {
			if (!(*it)->isInitialized()) {
				(*it)->setInit(true);
				(*it)->init();
				++it;
			}
			else if ((*it)->getPosition().x < 0 || (*it)->getPosition().x > StaticTools::GetResolution().first) {
				(*it)->destroy();
				++it;
			}
			else {
				(*it)->update(delta);

				for (auto it_sub : Entities) {
					if (it_sub->getID() != (*it)->getID() && it_sub->isCollidingWith(*it)) {
						it_sub->collision(Client, (*it));
					}
				}

				++it;
			}
		}
		else {
			++it;
		}
	}
}

void World::display(sf::RenderWindow &window)
{
	std::lock_guard<std::mutex> lock(Mutex);

	for (auto it : Entities) {
		window.draw(*it);
	}
}

void World::recycle(void)
{
	std::lock_guard<std::mutex> lock(Mutex);

	for (auto it : Entities) {
		it->recycle();
		delete (it);
	}
	Entities.clear();
}

AEntity *World::getEntityByID(uint8_t id)
{
	for (auto it : Entities) {
		if (it->getID() == id) {
			return (it);
		}
	}
	return (NULL);
}