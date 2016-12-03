#include "Mate.hpp"

Mate::Mate(void)
{
	setTargetFrame(2);
	setCurrentFrame(2);
	setVelocity(20.f);
	setID(1);
}

Mate::~Mate(void)
{
}


void Mate::init(void)
{
	_init = true;
	setOrigin(17, 8);

	sf::RectangleShape *shape = new sf::RectangleShape;
	shape->setSize(sf::Vector2f(34, 16));

	try {
		sf::Texture *texture = LevelResource::TheLevelResource.getTextureByKey("players");
		texture->setSmooth(true);

		setShape(shape);
		setTexture(texture);

		shape->setTextureRect(sf::IntRect(1, (getID() - 1) * 18, 33, 16));
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
		recycle();
	}
}

void Mate::destroy(void)
{
}