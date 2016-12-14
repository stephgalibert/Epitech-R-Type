#pragma once

#include "ALayout.hpp"
#include "StaticTools.hpp"
#include "ProjectResource.hpp"

class MessageLayout : public ALayout
{
public:
	MessageLayout(void);
	virtual ~MessageLayout(void);

	virtual void init(void);
	virtual bool input(InputHandler &input);
	virtual void update(float delta);
	virtual void recycle(void);

	void addMessage(std::string const& msg);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	void pop(void);

	float _delta;

	std::list<sf::Text> _texts;
	sf::Vector2f _resolution;
};

