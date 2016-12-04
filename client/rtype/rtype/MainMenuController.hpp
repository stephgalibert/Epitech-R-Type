#pragma once

#include <string>
#include <iostream>

#include "AController.hpp"
#include "MenuButton.hpp"

class MainMenuController : public AController
{
	static const uint32_t BUTTON_Y_SPACING;
	static const uint32_t BUTTON_Y_ORIGIN;
	static const uint32_t BUTTON_X_ALIGN;
	static const uint32_t TITLE_BASE_Y_POS;
	static const uint32_t TITLE_FINAL_Y_POS;
	static const uint32_t TITLE_CHAR_SPACING;
	static const uint32_t SPLASH_PX_PER_SEC;
	static const uint32_t SPLASH_INIT_POS;
	static const uint32_t SPLASH_TITLE_TARGET_POS;
	static const float KEYBOARD_EVENT_DELTA_MIN;

public:
	MainMenuController(void);
	virtual ~MainMenuController(void);

public:
	enum class State : short {
		ST_None = 0,
		ST_SplashStart = 1,
		ST_Splash1 = 1,
		ST_Splash2 = 2,
		ST_Splash3 = 3,
		ST_Menu = 4
	};

private:
	enum SelectedAction : short {
		PLAY = 0,
		QUIT = 1,
		NONE = -1
	};

public:
	virtual void init();
	virtual bool input(InputHandler &input);
	virtual void update(float delta);
	virtual void draw(sf::RenderWindow &window);
	virtual void recycle(void);
	void forceState(const State state);

private:
	void addKeyAction(const sf::Keyboard::Key key, bool (MainMenuController::*func)(void));
	void buildKeyActionsMap(void);
	void updateSplashFirstPhase(const float delta);
	void updateSplashSecondPhase(const float delta);
	void updateSplashThirdPhase(const float delta);
	void updateMenu(const float delta);
	void abortSplash(void);

private:
	bool keyUp(void);
	bool keyDown(void);
	bool keyReturn(void);

private:
	State _fsm;
	short _action;
	float _keyboardEventDelta;
	std::unordered_map<uint32_t, std::function<bool(void)>> _keyActions;

private:
	std::vector<sf::Sprite> _titleSprites;
	std::vector<MenuButton> _buttons;
};

