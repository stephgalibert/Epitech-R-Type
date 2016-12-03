#include "Explosion.hpp"

Explosion::Explosion(void)
{
}

Explosion::~Explosion(void)
{
}

void Explosion::init(void)
{
	_init = true;
	try {
		setTextureSize(sf::Vector2i(2048, 1536));
		setMatrixSize(sf::Vector2i(8, 6));
		computeCellSize();

		setOrigin(256 * 0.15f, 256 * 0.15f);
		sf::RectangleShape *shape = new sf::RectangleShape();
		shape->setTextureRect(sf::IntRect(0, 0, 256, 256));
		shape->setSize(sf::Vector2f(256 * 0.3f, 256 * 0.3f));

		sf::Texture *texture = LevelResource::TheLevelResource.getTextureByKey("explosions");
		texture->setSmooth(true);

		setShape(shape);
		setTexture(texture);

		LevelResource::TheLevelResource.getSoundByKey("explosions")->play();
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
		throw (std::runtime_error(e.what()));
	}
}

void Explosion::destroy(void)
{
}