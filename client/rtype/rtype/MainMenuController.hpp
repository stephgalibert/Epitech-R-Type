#pragma once

#include <string>
#include <iostream>

#include "AController.hpp"
#include "MenuButton.hpp"
#include "MenuServerBrowser.hpp"
#include "MenuTextForm.hpp"
#include "MenuConfirmPopup.hpp"
#include "MenuTextInputPopup.hpp"
#include "MenuCredits.hpp"
#include "MenuOptions.hpp"
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
	static const std::string FORM_GAME_NAME;
	static const std::string FORM_GAME_NAME_DEFAULT;
	static const std::string FORM_PASSWORD;
	static const std::string FORM_PASSWORD_DEFAULT;
	static const std::string FORM_PLAYER_NAME;
	static const std::string FORM_PLAYER_NAME_DEFAULT;

public:
	MainMenuController(IClient &client);
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
		ST_Username = 25,
		ST_Creating = 30,
		ST_ConfirmCreate = 35,
		ST_Credits = 40,
		ST_Options = 50
	};

public:
	enum SelectedAction : short {
		PLAY = 0,
		CREATE = 1,
		OPTIONS = 2,
		QUIT = 3,
		CREDITS = 4,
		NONE = -1
	};

public:
	struct ConnectData {
		std::string game;
		std::string password;
		std::string username;
		std::string hostIp;
		std::string port;
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
	void restartMusic(void) const;
	short pullAction(void);
	ConnectData const &getConnectData(void) const;
	void addBrowserEntry(GetParty const &data);
	void clearConnectData(void);

private:
	void addKeyAction(const sf::Keyboard::Key key, bool (MainMenuController::*func)(void));
	void buildKeyActionsMap(void);
	void updateSplashFirstPhase(const float delta);
	void updateSplashSecondPhase(const float delta);
	void updateSplashThirdPhase(const float delta);
	void updateSplashFourthPhase(const float delta);
	void updateMenu(const float delta);
	void abortSplash(void);
	bool handleCreatingInput(InputHandler &input);
	bool handleCreateConfirmPopupInput(InputHandler &input);
	bool handleSelectingInput(InputHandler &input);
	bool handleUsernamePopupInput(InputHandler &input);
	bool handleMenuInput(InputHandler &input);
	bool handleSplashInput(InputHandler &input);
	bool handleCreditsInput(InputHandler &input);
	bool handleOptionsInput(InputHandler &input);


private:
	bool keyUp(void);
	bool keyPageUp(void);
	bool keyDown(void);
	bool keyPageDown(void);
	bool keyReturn(void);

private:
	IClient &_client;
	State _fsm;
	short _action;
	float _keyboardEventDelta;
	short _pushAction;
	int _selectedServer;
	std::unordered_map<uint32_t, std::function<bool(void)> > _keyActions;
	uint8_t _buttonsAlpha;
	ConnectData _connectData;

private:
	std::vector<sf::Sprite> _titleSprites;
	std::vector<MenuButton> _buttons;
	MenuServerBrowser _browser;
	MenuTextForm _form;
	MenuConfirmPopup _confirmPopup;
	MenuTextInputPopup _inputPopup;
	MenuCredits _creditsScreen;
	MenuOptions _optionsScreen;
};
