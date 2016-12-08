#pragma once

#include "AController.hpp"

class LoadingController : public AController
{
public:
	LoadingController(void);
	virtual ~LoadingController(void);

	virtual void init(void);
	virtual bool input(InputHandler &input);
	virtual void update(float delta);
	virtual void draw(sf::RenderWindow &window);
	virtual void recycle(void);

	void setTextColor(sf::Color const& color);
	void setTextSize(size_t size);
	void setText(std::string const& text);
	void setBaseText(std::string const& text);

private:
	void updateTextSize(void);

	float _delta;
	sf::Text _text;
	std::string _string;
	std::string _point;
	std::pair<short, short> _resolution;
};

