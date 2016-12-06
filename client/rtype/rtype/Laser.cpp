#include "Laser.hpp"

Laser::Laser(void)
	: _shape(NULL),
	_delta(0),
	_currentFrame(0),
	_color(1)
{
	setCollisionType(COLLISION_FATAL);
	setVelocity(230.f);
}

Laser::~Laser(void)
{
}

void Laser::init(void)
{
	_shape = new sf::RectangleShape;
	_shape->setSize(sf::Vector2f(18, 14));
	setOrigin(9, 7);

	try {
		initFrame();

		sf::Texture *texture = LevelResource::TheLevelResource.getTextureByKey("shots" + std::to_string(_color));
		texture->setSmooth(true);

		setShape(_shape);
		setTexture(texture);

		getShape()->setTextureRect(_frames.at(0)[0]);
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
		//throw (std::runtime_error(e.what()));
	}
}

void Laser::update(float delta)
{
	_delta += delta;

	updateFrame();
	AProjectile::update(delta);
}

void Laser::destroy(void)
{
}

void Laser::collision(IClient *client, ACollidable *other)
{
	(void)client;
	if (other->getCollisionType() == COLLISION_FATAL) {
		recycle();
	}
}

void Laser::setColor(uint8_t color)
{
	_color = color;
}

void Laser::updateFrame(void)
{
	if (_shape && _delta > 0.2f) {

		sf::IntRect const& rect = _frames.at(0)[1];
		setOrigin(rect.width / 2.f, rect.height / 2.f);
		_shape->setSize(sf::Vector2f((float)rect.width, (float)rect.height));
		_shape->setTextureRect(rect);

		_delta = 0;
	}
}

void Laser::initFrame(void)
{
	_frames[0][0] = sf::IntRect(231, 102, 18, 14);
	_frames[0][1] = sf::IntRect(249, 104, 18, 10);

	_currentFrame = 0;
}