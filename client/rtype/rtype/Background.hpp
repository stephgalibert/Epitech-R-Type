#pragma once

#include <unordered_map>
#include <functional>

#include "ALayer.hpp"
#include "StaticTools.hpp"

class Background : public ALayer
{
public:
	Background(ProjectResource &resource);
	virtual ~Background(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(void);

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

	float _delta;
	State _fsm;

	std::unordered_map<State, std::function<void(float)> > _states;
	sf::Vector2i _resolution;
	//Fader *_fader;
};

