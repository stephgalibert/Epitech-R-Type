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
	setOrigin(17, 8);
	sf::RectangleShape *shape = new sf::RectangleShape;
	shape->setSize(sf::Vector2f(34, 16));
	setPosition(20, 80);

	try {
		sf::Texture *texture = LevelResource::TheLevelResource.getTextureByKey("players");

		texture->setSmooth(true);
		shape->setTextureRect(sf::IntRect(1, (getID() - 1) * 18, 33, 16));

		setShape(shape);
		setTexture(texture);
	}
	catch (std::exception const& e) {
		delete (shape);
		StaticTools::Log << e.what() << std::endl;
	}
}

void Mate::destroy(void)
{

}