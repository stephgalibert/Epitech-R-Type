#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>

#include <SFML/Graphics.hpp>

class SplashScreen //: public ALayer
{
public:
	SplashScreen(void);
	~SplashScreen(void);

	void init(void);
	void update(float delta);

	void draw(sf::RenderWindow &window);

	bool isFinished(void) const;

private:
	enum class State : short
	{
		ST_None = 0,
		ST_Increase = 1,
		ST_Fix = 2,
		ST_Decrease = 3,
		ST_Finished = 4
	};

private:
	void st_none(float delta);
	void st_increase(float delta);
	void st_fix(float delta);
	void st_decrease(float delta);
	void st_finished(float delta);
	std::unordered_map<State, std::function<void(float)> > _states;

	sf::Texture _texture;
	sf::Sprite _sprite;

	sf::RectangleShape _rect;

	State _fsm;
	float _delta;
	bool _finished;
};

