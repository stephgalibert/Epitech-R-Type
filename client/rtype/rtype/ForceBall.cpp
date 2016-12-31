#include "ForceBall.hpp"

const float ForceBall::COEF_RESIZE = 1.3f;

ForceBall::ForceBall(void)
{
	_delta = 0;
	_currentFrame = 0;
	_shape = NULL;
	initFrame();
}

ForceBall::~ForceBall(void)
{
}

void ForceBall::init(void)
{
	try {
		_shape = new sf::RectangleShape;
		_shape->setSize(sf::Vector2f(18 * COEF_RESIZE, 14 * COEF_RESIZE));
		setOrigin((14 * COEF_RESIZE) / 2, (18 * COEF_RESIZE) / 2);

		sf::Texture *texture = ProjectResource::TheProjectResource.getTextureByKey("force");
		texture->setSmooth(true);

		setShape(_shape);
		setTexture(texture);

		getShape()->setTextureRect(_frames.at(_currentFrame));
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
}

void ForceBall::update(float delta)
{
	_delta += delta;

	updateFrame();
}

void ForceBall::destroy(IClient &client)
{
	(void)client;
}

void ForceBall::collision(IClient *client, AEntity *other)
{
	(void)client;
	(void)other;
}

void ForceBall::applyCollision(CollisionType type, AEntity *other)
{
	(void)type;
	(void)other;
}

void ForceBall::initFrame(void)
{
	_frames.emplace_back(0, 1, 18, 14);
	_frames.emplace_back(18, 1, 18, 14);
	_frames.emplace_back(34, 1, 18, 14);
	_frames.emplace_back(51, 1, 18, 16);
	_frames.emplace_back(68, 3, 18, 14);
	_frames.emplace_back(85, 3, 18, 14);
	_frames.emplace_back(102, 3, 18, 14);
	_frames.emplace_back(119, 3, 18, 14);
	_frames.emplace_back(136, 3, 18, 14);
	_frames.emplace_back(153, 1, 18, 16);
	_frames.emplace_back(187, 1, 18, 14);
}

void ForceBall::updateFrame(void)
{
	if (_delta > 0.08f) {
		++_currentFrame;

		if (_currentFrame == _frames.size()) {
			_currentFrame = 0;
		}

		sf::IntRect const& rect = _frames.at(_currentFrame);
		setOrigin((rect.width * COEF_RESIZE) / 2.f, (rect.height * COEF_RESIZE) / 2.f);
		_shape->setSize(sf::Vector2f((float)rect.width, (float)rect.height));
		_shape->setTextureRect(rect);

		_delta = 0;
	}
}