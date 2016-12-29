#include "World.hpp"

std::list<AEntity *> World::Entities;
std::queue<AEntity *> World::Queue;
std::mutex World::Mutex;
IClient *World::Client = NULL;
Player **World::ThePlayer = NULL;
QuadTree *World::Region = NULL;

void World::init(Player **player, IClient *client)
{
	ThePlayer = player;
	Client = client;

	std::pair<short, short> resolution = StaticTools::GetResolution();
	sf::FloatRect rect = sf::FloatRect(0, 0, resolution.first, resolution.second);
	Region = new QuadTree(0, rect);
}

void World::update(float delta)
{
	//std::lock_guard<std::mutex> lock(Mutex);
	std::list<AEntity *>::iterator it = std::begin(Entities);
	std::vector<AEntity *> collision;

	Region->clear();
	while (it != std::end(Entities)) {
		sf::Vector2f const& pos = (*it)->getPosition();
		if ((*it)->isWaitingForRecycle() ||
				pos.x < -100 - ((*it)->getBoundingBox().width / 2) || pos.x - 100 - ((*it)->getBoundingBox().width / 2) > StaticTools::GetResolution().first ||
				pos.y < -100 - ((*it)->getBoundingBox().height / 2) || pos.y - 100 - ((*it)->getBoundingBox().height / 2) > StaticTools::GetResolution().second) {

			(*it)->destroy(*Client);
			delete (*it);
			it = Entities.erase(it);
		}
		else if ((*it)->isReadyForInit()) {
			if (!(*it)->isInitialized()) {
				(*it)->setInit(true);
				(*it)->init();
				++it;
			}
			else {
				(*it)->update(delta);

				if (!(*it)->isWaitingForRecycle()) {
					Region->insert((*it));
					collision.clear();

					Region->retrieve(collision, (*it));
					for (auto it_sub : collision) {
						if (it_sub->isInitialized() && it_sub->getID() != (*it)->getID()
							&& it_sub->isCollidingWith(*it)) {
							it_sub->collision(Client, (*it));
						}
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

AEntity *World::getEntityByID(uint16_t id)
{
	std::lock_guard<std::mutex> lock(Mutex);

	for (auto it : Entities) {
		if (it->getID() == id) {
			return (it);
		}
	}
	return (NULL);
}

Player *World::GetPlayer(void)
{
	if (ThePlayer) {
		return (*ThePlayer);
	}
	return (NULL);
}