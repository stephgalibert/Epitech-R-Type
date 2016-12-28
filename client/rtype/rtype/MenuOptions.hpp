#pragma once

#include "SFML/Graphics.hpp"

#include "MenuTextForm.hpp"

class MenuOptions : public sf::Drawable {
	static const std::string FORM_HOST_FIELD;
	static const std::string FORM_PORT_FIELD;

public:
	MenuOptions();
	virtual ~MenuOptions();

public:
	void init(void);
	bool input(InputHandler &input);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	std::string const &getHost(void) const;
	std::string const &getPort(void) const;
	MenuTextForm const &getForm(void) const;

public:
	void setPosition(sf::Vector2f const &position);
	void setWidth(const float width);
	void setHost(std::string const &host);
	void setPort(std::string const &port);

private:
	MenuTextForm _form;
};

