#pragma once

#include <vector>

#include <SFML\Graphics.hpp>

//#include "World.hpp"
#include "ProjectResource.hpp"

class World;

class ADrawable : public sf::Drawable, public sf::Transformable
{
public:
	ADrawable(ProjectResource &resource);
	virtual ~ADrawable(void);

	virtual void init(void) = 0;
	virtual void update(float delta) = 0;
	virtual void destroy(void) = 0;

protected:
	void setShape(sf::Shape *shape);
	void setTexture(sf::Texture *texture);

	ProjectResource &getResource(void);

	sf::Shape *getShape(void) const;
	sf::Texture *getTexture(void) const;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	ProjectResource &_resource;
	sf::Shape *_shape;
	sf::Texture *_texture;

};