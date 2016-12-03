#pragma once

#include <string>
#include <iostream>

#include "AController.hpp"
#include "Background.hpp"

class MainMenuController : public AController
{
	static const uint32_t TITLE_BASE_Y_POS;
	static const uint32_t TITLE_FINAL_Y_POS;
	static const uint32_t TITLE_CHAR_SPACING;
	static const uint32_t SPLASH_PX_PER_SEC;
	static const uint32_t SPLASH_INIT_POS;
	static const uint32_t SPLASH_TITLE_TARGET_POS;

public:
	MainMenuController(void);
	virtual ~MainMenuController(void);

public:
	virtual void init(void);
	virtual bool input(InputHandler &input);
	virtual void update(float delta);
	virtual void draw(sf::RenderWindow &window);
	virtual void recycle(void);

private:
	void updateSplashFirstPhase(const float delta);
	void updateSplashSecondPhase(const float delta);
	void updateSplashThirdPhase(const float delta);
	void updateMenu(void);
	void abortSplash(void);

private:
	enum class State : short
	{
		ST_None = 0,
		ST_Splash1 = 1,
		ST_Splash2 = 2,
		ST_Splash3 = 3,
		ST_Menu = 4
	};

private:
	State _fsm;

private:
	std::vector<sf::Sprite> _titleSprites;
};

