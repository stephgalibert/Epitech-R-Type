#pragma once

#include "ALayout.hpp"
#include "StaticTools.hpp"

#include "ProjectResource.hpp"

class EscapeLayout : public ALayout
{
public:
	EscapeLayout(void);
	virtual ~EscapeLayout(void);

	virtual void init(void);
	virtual bool input(InputHandler &input);
	virtual void update(float delta);
	virtual void recycle(void);

	bool isVisible(void) const;
	bool exit(void) const;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void initQuitButton(void);
	void initResumeButton(void);
	void initBackground(void);

	void up(void);
	void down(void);
	void enter(void);

private:
	float _delta;
	float _deltaLastAction;

	std::vector<sf::Text> _texts;
	std::vector<sf::RectangleShape> _buttons;

	sf::RectangleShape _background;

	std::pair<short, short> _resolution;
	bool _visible;
	bool _exit;
	size_t _selected;
};

