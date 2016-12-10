#include "LoadedPowdered.hpp"

LoadedPowdered::LoadedPowdered(void)
{
}

LoadedPowdered::~LoadedPowdered(void)
{
}

void LoadedPowdered::init(void)
{
	_shape = new sf::RectangleShape;
	_shape->setSize(sf::Vector2f(30 * 1.3f, 34 * 1.3f));
	setOrigin(15.f * 1.3f, 17.f * 1.3f);

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

void LoadedPowdered::update(float delta)
{
	_delta += delta;

	updateFrame();
}

void LoadedPowdered::destroy(void)
{
}

void LoadedPowdered::collision(IClient *client, AEntity *other)
{
	(void)client;
	(void)other;
}

void LoadedPowdered::move(float delta)
{
	(void)delta;
}

void LoadedPowdered::setColor(uint8_t color)
{
	_color = color;
}

void LoadedPowdered::initFrame(void)
{
	_frames.emplace_back(1, 50, 33, 34);
	_frames.emplace_back(34, 51, 30, 30);
	_frames.emplace_back(67, 53, 31, 30);
	_frames.emplace_back(102, 54, 27, 27);
	_frames.emplace_back(134, 55, 31, 24);
	_frames.emplace_back(167, 57, 28, 20);
	_frames.emplace_back(199, 58, 25, 17);
	_frames.emplace_back(232, 59, 22, 14);
}

void LoadedPowdered::updateFrame(void)
{
	if (_delta > 0.1f) {
		if (_currentFrame < _frames.size() - 1) {
			++_currentFrame;
		}
		else {
			_currentFrame = 0;
		}

		sf::IntRect const& r = _frames.at(_currentFrame);
		_shape->setSize(sf::Vector2f((float)r.width * 1.3f, (float)r.height * 1.3f));
		setOrigin((r.width * 1.3f) / 2.f, (r.height * 1.3f) / 2.f);
		getShape()->setTextureRect(r);
		_delta = 0.f;
	}
}