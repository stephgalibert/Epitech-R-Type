#include "IncreaseNumberOfCanon.hpp"

IncreaseNumberOfCanon::IncreaseNumberOfCanon(void)
{
	_delta = 0;
	_currentFrame = 0;
}

IncreaseNumberOfCanon::~IncreaseNumberOfCanon(void)
{
}

void IncreaseNumberOfCanon::init(void)
{
	sf::RectangleShape *shape = new sf::RectangleShape;
	shape->setSize(sf::Vector2f(31, 29));
	setOrigin(15.5f, 14.5f);

	try {
		initFrame();

		sf::Texture *texture = ProjectResource::TheProjectResource.getTextureByKey("powerups1");
		texture->setSmooth(true);

		setShape(shape);
		setTexture(texture);

		getShape()->setTextureRect(_frames.at(0));
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
}

void IncreaseNumberOfCanon::update(float delta)
{
	_delta += delta;
	
	updateFrame();
}

void IncreaseNumberOfCanon::destroy(void)
{
}

void IncreaseNumberOfCanon::attachToEntity(AEntity *entity)
{
	sf::Vector2f const& pos = entity->getPosition();
	setPosition(pos.x + 50, pos.y + 2);
}

bool IncreaseNumberOfCanon::fire(IClient *client, uint16_t playerID, sf::Vector2i const& pos, uint8_t velocity, uint8_t angle, uint8_t level)
{
	client->write(std::make_shared<CMDFire>(MissileType::MT_FriendFire_Lv1, 0, playerID, pos.x + 10, pos.y, velocity, angle, 0, level));
	client->write(std::make_shared<CMDFire>(MissileType::MT_FriendFire_Lv1, 0, playerID, pos.x + 10, pos.y - 20, velocity, angle, 0, level));
	client->write(std::make_shared<CMDFire>(MissileType::MT_FriendFire_Lv1, 0, playerID, pos.x + 10, pos.y + 20, velocity, angle, 0, level));
	return (true);
}

void IncreaseNumberOfCanon::initFrame(void)
{
	_frames.push_back(sf::IntRect(172, 344, 31, 29));
	_frames.push_back(sf::IntRect(204, 346, 31, 24));
	_frames.push_back(sf::IntRect(236, 343, 31, 30));
	_frames.push_back(sf::IntRect(269, 341, 31, 34));
}

void IncreaseNumberOfCanon::updateFrame()
{
	if (_delta > 0.1f) {
		++_currentFrame;
		if (_currentFrame == _frames.size()) {
			_currentFrame = 0;
		}
		sf::IntRect const& rect = _frames.at(_currentFrame);
		getShape()->setTextureRect(rect);
		//setOrigin(rect.width / 2.f, rect.height / 2.f);
		_delta = 0;
	}
}