#pragma once

#include <unordered_map>
#include <functional>

#include "ADrawable.hpp"
#include "LevelResource.hpp"
#include "StaticTools.hpp"

class Background
{
public:
	Background(void);
	virtual ~Background(void);

	void init(void);
	void update(float delta);
	void destroy(void);
	void draw(sf::RenderWindow &window);

private:
	enum class State : short
	{
		ST_None = 0,
		ST_FadeIn = 1,
		ST_Parallax = 2
	};

private:
	void st_none(float delta);
	void st_fadeIn(float delta);
	void st_parallax(float delta);
	std::unordered_map<State, std::function<void(float)> > _states;

	float _delta;
	State _fsm;
	sf::Vector2i _resolution;

	sf::Texture *_texture1;
	sf::Texture *_texture2;
	sf::RectangleShape _shape1;
	sf::RectangleShape _shape2;
	//Fader *_fader;
};

