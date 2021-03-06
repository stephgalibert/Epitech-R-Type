#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "ProjectResource.hpp"
#include "IClient.hpp"

class ADrawable : public sf::Drawable, public sf::Transformable
{
public:
	static const int VISIBILITY_GONE = 1;
	static const int VISIBILITY_VISIBLE = 2;

public:
	ADrawable();
	virtual ~ADrawable(void);

	virtual void init(void) = 0;
	virtual void update(float delta) = 0;
	virtual void destroy(IClient &client) = 0;

	void recycle(void);
	bool isWaitingForRecycle(void) const;

	void setInit(bool value);
	bool isInitialized(void) const;

	void setVisiblity(int visibility);

protected:
	void setShape(sf::Shape *shape);
	void setTexture(sf::Texture *texture);

	sf::Shape *getShape(void) const;
	sf::Texture *getTexture(void) const;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Shape *_shape;
	sf::Texture *_texture;
	bool _waitingForRecycle;
	bool _init;
};
