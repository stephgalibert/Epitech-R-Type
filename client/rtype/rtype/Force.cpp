#include "Force.hpp"

Force::Force(void)
{
	_delta = 0;
	_level = 0;
	_currentFrame = 0;
	_pos = Position::Forward;
}

Force::~Force(void)
{
}

void Force::init(void)
{
	sf::RectangleShape *shape = new sf::RectangleShape;
	shape->setSize(sf::Vector2f(29, 24));
	setOrigin(14.5f, 12.f);

	try {
		initFrame();

		sf::Texture *texture = ProjectResource::TheProjectResource.getTextureByKey("powerups1");
		texture->setSmooth(true);

		setShape(shape);
		setTexture(texture);

		getShape()->setTextureRect(_frames[0].at(0));
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
}

void Force::update(float delta)
{
	_delta += delta;

	updateFrame();
}

void Force::destroy(IClient &client)
{
	(void)client;
}

std::string Force::getType(void) const
{
	return ("force");
}

void Force::attachToEntity(AEntity *entity)
{
	sf::Vector2f const& pos = entity->getPosition();

	if (_pos == Position::Forward || _level == 0) {
		setPosition(pos.x + 50, pos.y + 2);
	}
	else {
		setPosition(pos.x - 50, pos.y + 2);
	}
}

bool Force::fire(IClient *client, uint16_t playerID, sf::Vector2i const& pos, uint8_t velocity, float angle, uint8_t level)
{
	if (_level == 0) {
		client->write(std::make_shared<CMDFire>(MissileType::Laser, 0, playerID, pos.x + 10, pos.y, velocity, angle, 0, level));
		client->write(std::make_shared<CMDFire>(MissileType::Laser, 0, playerID, pos.x + 10, pos.y - 20, velocity, angle, 0, level));
		client->write(std::make_shared<CMDFire>(MissileType::Laser, 0, playerID, pos.x + 10, pos.y + 20, velocity, angle, 0, level));
	}
	else if (_level == 1) {
		if (_pos == Position::Forward) {
			client->write(std::make_shared<CMDFire>(MissileType::Laser, 0, playerID, pos.x + 10, pos.y, velocity, angle, 0, level));
			client->write(std::make_shared<CMDFire>(MissileType::Laser, 0, playerID, pos.x + 10, pos.y - 20, velocity, angle - 10, 0, level));
			client->write(std::make_shared<CMDFire>(MissileType::Laser, 0, playerID, pos.x + 10, pos.y + 20, velocity, angle + 10, 0, level));
		}
		else {
			client->write(std::make_shared<CMDFire>(MissileType::DoubleLaser, 0, playerID, pos.x - 90, pos.y, velocity, angle, 0, level));
		}
	}
	return (true);
}

bool Force::canBeCumulated(void) const
{
	return (true);
}

void Force::upgrade(void)
{
	if (_level < _frames.size()) {
		++_level;
	}
}

void Force::inversePosition(void)
{
	if (_pos == Position::Forward) {
		_pos = Position::Backward;
	}
	else {
		_pos = Position::Forward;
	}
}

void Force::initFrame(void)
{
	_frames[0].push_back(sf::IntRect(119, 68, 29, 24));
	_frames[0].push_back(sf::IntRect(149, 70, 29, 20));
	_frames[0].push_back(sf::IntRect(180, 71, 29, 18));
	_frames[0].push_back(sf::IntRect(211, 71, 29, 18));
	_frames[0].push_back(sf::IntRect(241, 71, 29, 18));
	_frames[0].push_back(sf::IntRect(271, 70, 29, 20));

	_frames[1].push_back(sf::IntRect(172, 344, 31, 29));
	_frames[1].push_back(sf::IntRect(204, 346, 31, 24));
	_frames[1].push_back(sf::IntRect(236, 343, 31, 30));
	_frames[1].push_back(sf::IntRect(269, 341, 31, 34));
}

void Force::updateFrame(void)
{
	if (_delta > 0.1f) {
		++_currentFrame;
		if (_currentFrame >= _frames[_level].size()) {
			_currentFrame = 0;
		}
		sf::IntRect const& rect = _frames[_level].at(_currentFrame);
		getShape()->setTextureRect(rect);
		_delta = 0;
	}
}