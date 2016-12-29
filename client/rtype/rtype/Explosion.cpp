#include "Explosion.hpp"

Explosion::Explosion(void)
{
	_shape = NULL;
	_w = 256 * 0.2f;
	_h = 256 * 0.2f;
}

Explosion::~Explosion(void)
{
}

void Explosion::init(void)
{
	try {
		setTextureSize(sf::Vector2i(2048, 1536));
		setMatrixSize(sf::Vector2i(8, 6));
		computeCellSize();

		_shape = new sf::RectangleShape();
		_shape->setTextureRect(sf::IntRect(0, 0, 256, 256));
		_shape->setSize(sf::Vector2f(_w, _h));
		setOrigin(_w / 2, _h / 2);

		sf::Texture *texture = ProjectResource::TheProjectResource.getTextureByKey("explosions");
		texture->setSmooth(true);

		setShape(_shape);
		setTexture(texture);

		ProjectResource::TheProjectResource.getSoundByKey("explosions")->play();
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
		throw (std::runtime_error(e.what()));
	}
}

void Explosion::destroy(IClient &client)
{
	(void)client;
}

void Explosion::setSize(float w, float h)
{
	if (_shape) {
		_shape->setSize(sf::Vector2f(w, h));
		setOrigin(w / 2, h / 2);
	}
	else {
		_w = w;
		_h = h;
	}
}