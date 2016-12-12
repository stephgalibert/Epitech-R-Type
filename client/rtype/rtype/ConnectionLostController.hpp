#pragma once

#include "AController.hpp"

class ConnectionLostController : public AController
{
public:
	ConnectionLostController(void);
	virtual ~ConnectionLostController(void);

	virtual void init(void);
	virtual bool input(InputHandler &input);
	virtual void update(float delta);
	virtual void draw(sf::RenderWindow &window);
	virtual void recycle(void);

	void setTextColor(sf::Color const& color);
	void setTextSize(size_t size);
	void setText(std::string const& text);
	void setBaseText(std::string const& text);
	void updateTextSize(void);

private:
	float _delta;
	sf::Text _text;
	std::string _string;
	std::pair<short, short> _resolution;
};

