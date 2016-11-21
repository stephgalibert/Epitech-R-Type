#pragma once

#include <vector>

#include <SFML\Graphics.hpp>

#include "ProjectResource.hpp"

class ADrawable : public sf::Drawable, public sf::Transformable
{
public:
	ADrawable(ProjectResource &resource);
	virtual ~ADrawable(void);

	virtual void init(void) = 0;
	virtual void update(float delta) = 0;
	virtual void destroy(void) = 0;

	ProjectResource &getResource(void);

protected:
	void setShape(sf::Shape *shape);
	void setTexture(sf::Texture *texture);

	sf::Shape *getShape(void) const;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	ProjectResource &_resource;
	sf::Shape *_shape;
	sf::Texture *_texture;

};