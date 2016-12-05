#include "Mate.hpp"

Mate::Mate(void)
{
	_targetFrame = 0;
	_currentFrame = 0;
	setVelocity(0.f);
	_currentDirection = FRAME_MID;
}

Mate::~Mate(void)
{
}


void Mate::init(void)
{
	sf::RectangleShape *shape = new sf::RectangleShape;
	shape->setSize(sf::Vector2f(65, 38));
	setOrigin(32.5f, 19);

	try {
		initFrame();

		sf::Texture *texture = LevelResource::TheLevelResource.getTextureByKey("players");
		texture->setSmooth(true);

		setShape(shape);
		setTexture(texture);

		sf::IntRect const& r = _frames.at(FRAME_MID);
		getShape()->setTextureRect(sf::IntRect(r.width, r.top, r.width, r.height));
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
		recycle();
	}
}

void Mate::update(float delta)
{
	_delta += delta;

	if (_currentDirection != FRAME_EXP) {
		uint8_t direction = getDirection();
		_targetFrame = 0;
		_currentDirection = FRAME_MID;

		if (direction != 0) {
			if (direction == NORTH) {
				_currentDirection = FRAME_TOP;
			}
			else if (direction == SOUTH) {
				_currentDirection = FRAME_BOT;
			}
			else if (direction & NORTH && direction & EAST) {
				_currentDirection = FRAME_TOP;
			}
			else if (direction & SOUTH && direction & EAST) {
				_currentDirection = FRAME_BOT;
			}

			if (direction & WEAST) {
			}
			else if (direction & EAST) {
				_targetFrame = 3;
			}
		}
	}

	updateFrame();
	ANPC::update(delta);
}

void Mate::destroy(void)
{
}

void Mate::collision(IClient *client, ACollidable *other)
{
	(void)client;
	if (getCollisionType() != COLLISION_NONE
		&& other->getCollisionType() == COLLISION_FATAL
		&& _currentDirection != FRAME_EXP) {

		Explosion *explosion = World::TheWorld.spawnEntity<Explosion>();
		explosion->setPosition(getPosition());

		LevelResource::TheLevelResource.getSoundByKey("explosions")->play();
		_currentDirection = FRAME_EXP;
		_currentFrame = 0;
		_targetFrame = 5;

		setAngle(-1);
		setVelocity(0);
	}
	

}

void Mate::initFrame(void)
{
	switch (getID())
	{
	case 1:
		_frames[FRAME_TOP] = sf::IntRect(0, 302, 64, 38);
		_frames[FRAME_MID] = sf::IntRect(0, 340, 64, 37);
		_frames[FRAME_BOT] = sf::IntRect(0, 377, 64, 38);
		_frames[FRAME_EXP] = sf::IntRect(0, 415, 64, 38);
		break;
	case 2:
		_frames[FRAME_TOP] = sf::IntRect(0, 152, 64, 37);
		_frames[FRAME_MID] = sf::IntRect(0, 189, 64, 37);
		_frames[FRAME_BOT] = sf::IntRect(0, 226, 64, 38);
		_frames[FRAME_EXP] = sf::IntRect(0, 264, 64, 38);
		break;
	case 3:
		_frames[FRAME_TOP] = sf::IntRect(0, 453, 64, 37);
		_frames[FRAME_MID] = sf::IntRect(0, 490, 64, 37);
		_frames[FRAME_BOT] = sf::IntRect(0, 527, 64, 38);
		_frames[FRAME_EXP] = sf::IntRect(0, 565, 64, 38);
		break;
	case 4:
		_frames[FRAME_TOP] = sf::IntRect(0, 2, 64, 37);
		_frames[FRAME_MID] = sf::IntRect(0, 39, 64, 37);
		_frames[FRAME_BOT] = sf::IntRect(0, 76, 64, 38);
		_frames[FRAME_EXP] = sf::IntRect(0, 114, 64, 38);
		break;
	default:
		break;
	}
}

void Mate::updateFrame(void)
{
	if (_delta > 0.08f) {

		if (_currentDirection == FRAME_EXP && _currentFrame == 5) {
			recycle();
		}

		if (_currentFrame != _targetFrame) {
			if (_currentFrame < _targetFrame) {
				++_currentFrame;
			}
			else if (_currentFrame > _targetFrame) {
				--_currentFrame;
			}
		}
		if (_currentDirection != FRAME_EXP && _currentFrame == 3) {
			if (_decrease) {
				--_currentFrame;
				_decrease = false;
			}
			else {
				_decrease = true;
			}
		}
		else if (_currentDirection != FRAME_EXP && _currentFrame == 0) {
			if (_decrease) {
				++_currentFrame;
				_decrease = false;
			}
			else {
				_decrease = true;
			}
		}
		
		sf::IntRect const& r = _frames.at(_currentDirection);
		getShape()->setTextureRect(sf::IntRect(_currentFrame * r.width, r.top, r.width, r.height));
		_delta = 0.f;
	}
}
