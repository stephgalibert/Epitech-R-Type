#pragma once

#include <string>
#include <iostream>

#include "AController.hpp"
#include "MenuButton.hpp"
#include "MenuServerBrowser.hpp"
#include "MenuTextForm.hpp"
#include "IClient.hpp"

class MainMenuController : public AController
{
	static const uint32_t BUTTON_Y_SPACING;
	static const uint32_t BUTTON_Y_ORIGIN;
	static const uint32_t BUTTON_X_ALIGN;
	static const float TITLE_LETTER_SCALE;
	static const uint32_t TITLE_LETTER_HEIGHT;
	static const uint32_t TITLE_FINAL_BOTTOM_OFFSET;
	static const uint32_t TITLE_BASE_Y_POS;
	static const uint32_t TITLE_FINAL_Y_POS;
	static const uint32_t TITLE_CHAR_SPACING;
	static const float SPLASH_PX_PER_SEC;
	static const uint32_t SPLASH_INIT_POS;
	static const uint32_t SPLASH_TITLE_TARGET_POS;
	static const float KEYBOARD_EVENT_DELTA_MIN;
	static const float SERVER_BROWSER_POS_X;
	static const float SERVER_BROWSER_POS_Y;
	static const float SERVER_BROWSER_WIDTH;
	static const size_t SERVER_BROWSER_ITEMS_SHOWN;

public:
	MainMenuController(IClient &_client);
	virtual ~MainMenuController(void);

public:
	enum class State : short {
		ST_None = 0,
		ST_SplashStart = 1,
		ST_Splash1 = 1,
		ST_Splash2 = 2,
		ST_Splash3 = 3,
		ST_Splash4 = 4,
		ST_Menu = 10,
		ST_Selecting = 20,
		ST_Creating = 30
	};

public:
	enum SelectedAction : short {
		PLAY = 0,
		CREATE = 1,
		QUIT = 2,
		NONE = -1
	};

public:
	struct ConnectData {
		std::string game;
		std::string password;
	};

public:
	virtual void init();
	virtual bool input(InputHandler &input);
	virtual void update(float delta);
	virtual void draw(sf::RenderWindow &window);
	virtual void recycle(void);
	void forceState(const State state);
	void mute(void) const;
	void unmute(void) const;
	short pullAction(void);
	ConnectData const &getConnectData(void) const;

private:
	void addKeyAction(const sf::Keyboard::Key key, bool (MainMenuController::*func)(void));
	void buildKeyActionsMap(void);
	void updateSplashFirstPhase(const float delta);
	void updateSplashSecondPhase(const float delta);
	void updateSplashThirdPhase(const float delta);
	void updateSplashFourthPhase(const float delta);
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
	std::unordered_map<uint32_t, std::function<bool(void)> > _keyActions;
	short _pushAction;
	uint8_t _buttonsAlpha;
	int _selectedServer;
	IClient &_client;
	ConnectData _connectData;

private:
	std::vector<sf::Sprite> _titleSprites;
	std::vector<MenuButton> _buttons;
	MenuServerBrowser _browser;
	MenuTextForm _form;

	/* TEST ONLY */
private:
	std::vector<std::string> _browserContent;
};
