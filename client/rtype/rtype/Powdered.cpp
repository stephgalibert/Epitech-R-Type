#include "Powdered.hpp"

Powdered::Powdered(void)
	: _shape(NULL),
	  _delta(0),
	  _currentFrame(0),
	  _color(1),
	  _finished(false)
{
	setCollisionType(COLLISION_NONE);
}

Powdered::~Powdered(void)
{
}


void Powdered::init(void)
{
	_shape = new sf::RectangleShape;
	_shape->setSize(sf::Vector2f(12 * 1.3f, 12 * 1.3f));
	setOrigin(6 * 1.3f, 6 * 1.3f);

	try {
		initFrame();

		sf::Texture *texture = LevelResource::TheLevelResource.getTextureByKey("shots" + std::to_string(_color));
		texture->setSmooth(true);

		setShape(_shape);
		setTexture(texture);

		getShape()->setTextureRect(_frames.at(0));

	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
}

void Powdered::update(float delta)
{
	_delta += delta;

	updateFrame();
}

void Powdered::destroy(void)
{
}

void Powdered::collision(IClient *client, AEntity *other)
{
	(void)client;
	(void)other;
}

void Powdered::applyCollision(CollisionType type)
{
	(void)type;
}

void Powdered::move(float delta)
{
	(void)delta;
}

void Powdered::setColor(uint16_t color)
{
	_color = color;
}

bool Powdered::isAnimationFinished(void) const
{
	return (_finished);
}

void Powdered::initFrame(void)
{
	_frames.emplace_back(233, 86, 12, 12);
	_frames.emplace_back(215, 84, 16, 14);
}

void Powdered::updateFrame(void)
{
	if (_delta > 0.1f) {
		if (_currentFrame < 1) {
			++_currentFrame;
		
			sf::IntRect const& r = _frames.at(_currentFrame);
			_shape->setSize(sf::Vector2f(r.width * 1.3f, r.height * 1.3f));
			setOrigin((r.width / 2.f) * 1.3f, (r.height / 2.f) * 1.3f);
			getShape()->setTextureRect(r);
		}
		else {
			_finished = true;
		}
		_delta = 0.f;
	}
}