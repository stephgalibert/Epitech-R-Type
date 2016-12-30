#include "MainMenuController.hpp"
#include "MainMenuResource.hpp"

const uint32_t MainMenuController::BUTTON_Y_SPACING = 45;
const uint32_t MainMenuController::BUTTON_Y_ORIGIN = 50;
const uint32_t MainMenuController::BUTTON_X_ALIGN = StaticTools::GetResolution().first - 380;
const float MainMenuController::TITLE_LETTER_SCALE = 2.f;
const uint32_t MainMenuController::TITLE_LETTER_HEIGHT = static_cast<uint32_t>(56 * MainMenuController::TITLE_LETTER_SCALE);
const uint32_t MainMenuController::TITLE_FINAL_BOTTOM_OFFSET = 25;
const uint32_t MainMenuController::TITLE_BASE_Y_POS = (StaticTools::GetResolution().second / 2) - MainMenuController::TITLE_LETTER_HEIGHT;
const uint32_t MainMenuController::TITLE_FINAL_Y_POS = (StaticTools::GetResolution().second
	- MainMenuController::TITLE_LETTER_HEIGHT - MainMenuController::TITLE_FINAL_BOTTOM_OFFSET);
const uint32_t MainMenuController::TITLE_CHAR_SPACING = 15;
const float MainMenuController::SPLASH_PX_PER_SEC = StaticTools::GetResolution().first / 1.5f;
const uint32_t MainMenuController::SPLASH_INIT_POS = StaticTools::GetResolution().first;
const uint32_t MainMenuController::SPLASH_TITLE_TARGET_POS = StaticTools::GetResolution().first / 5;
const float MainMenuController::KEYBOARD_EVENT_DELTA_MIN = 0.13f;
const float MainMenuController::SERVER_BROWSER_POS_X = 75.f;
const float MainMenuController::SERVER_BROWSER_POS_Y = 60.f;
const float MainMenuController::SERVER_BROWSER_WIDTH = StaticTools::GetResolution().first / 2.f + 10.f;
const size_t MainMenuController::SERVER_BROWSER_ITEMS_SHOWN = 15u;
const std::string MainMenuController::FORM_GAME_NAME = "Game Name";
const std::string MainMenuController::FORM_GAME_NAME_DEFAULT = "room1";
const std::string MainMenuController::FORM_PASSWORD = "Password";
const std::string MainMenuController::FORM_PASSWORD_DEFAULT = "pwd1";
const std::string MainMenuController::FORM_PLAYER_NAME = "Player Name";
const std::string MainMenuController::FORM_PLAYER_NAME_DEFAULT = "Player";

MainMenuController::MainMenuController(IClient &client)
	: _client(client),
	_fsm(State::ST_SplashStart),
	_action(SelectedAction::NONE),
	_keyboardEventDelta(0.f),
	_pushAction(SelectedAction::NONE),
	_selectedServer(-1)
{
	buildKeyActionsMap();
}

MainMenuController::~MainMenuController(void)
{
	ProjectResource::TheProjectResource.getMusicByKey(ProjectResource::MAIN_THEME).stop();
}

void MainMenuController::init()
{
	try {
		MainMenuResource::menuResourceManager.load();
		sf::Font *menuFont = &ProjectResource::TheProjectResource.getFontByKey(ProjectResource::MAIN_FONT);

		_titleSprites.push_back(sf::Sprite(*MainMenuResource::menuResourceManager.getTextureByKey(MainMenuResource::LOGO_R)));
		_titleSprites.push_back(sf::Sprite(*MainMenuResource::menuResourceManager.getTextureByKey(MainMenuResource::LOGO_DOT)));
		_titleSprites.push_back(sf::Sprite(*MainMenuResource::menuResourceManager.getTextureByKey(MainMenuResource::LOGO_T)));
		_titleSprites.push_back(sf::Sprite(*MainMenuResource::menuResourceManager.getTextureByKey(MainMenuResource::LOGO_Y)));
		_titleSprites.push_back(sf::Sprite(*MainMenuResource::menuResourceManager.getTextureByKey(MainMenuResource::LOGO_P)));
		_titleSprites.push_back(sf::Sprite(*MainMenuResource::menuResourceManager.getTextureByKey(MainMenuResource::LOGO_E)));
		for (auto &sprite : _titleSprites) {
			sprite.setScale(TITLE_LETTER_SCALE, TITLE_LETTER_SCALE);
			sprite.setPosition(static_cast<float>(SPLASH_INIT_POS), static_cast<float>(TITLE_BASE_Y_POS));
		}

		_buttons.push_back(MenuButton("Browse servers", static_cast<short>(SelectedAction::PLAY), menuFont));
		_buttons.push_back(MenuButton("Create game", static_cast<short>(SelectedAction::CREATE), menuFont));
		_buttons.push_back(MenuButton("Options", static_cast<short>(SelectedAction::OPTIONS), menuFont));
		_buttons.push_back(MenuButton("Credits", static_cast<short>(SelectedAction::CREDITS), menuFont));
		_buttons.push_back(MenuButton("Quit", static_cast<short>(SelectedAction::QUIT), menuFont));
		
		
		_browser.setPosition(sf::Vector2f(SERVER_BROWSER_POS_X, SERVER_BROWSER_POS_Y));
		_browser.setSize(sf::Vector2f(SERVER_BROWSER_WIDTH, MenuServerBrowser::getHeightForItems(SERVER_BROWSER_ITEMS_SHOWN)));
		_browser.setFont(menuFont);

		_form.setPosition(_browser.getPosition());
		_form.addField(FORM_GAME_NAME, FORM_GAME_NAME_DEFAULT);
		_form.addField(FORM_PASSWORD, FORM_PASSWORD_DEFAULT);
		_form.addField(FORM_PLAYER_NAME, FORM_PLAYER_NAME_DEFAULT);
		_form.setSize(sf::Vector2f(SERVER_BROWSER_WIDTH, _form.getIdealHeight()));

		_confirmPopup.setFont(menuFont);
		_confirmPopup.setMessage("Confirm ?");
		_confirmPopup.centerOnScreen();

		_optionsScreen.init(menuFont);
		_optionsScreen.setWidth(SERVER_BROWSER_WIDTH);
		_optionsScreen.setPosition(_browser.getPosition());

		_creditsScreen.init(menuFont);
		_creditsScreen.setPosition(_browser.getPosition());

		_action = SelectedAction::PLAY;
		_fsm = State::ST_SplashStart;

		setMusicVolume(StaticTools::musicVolume);
		setSoundVolume(StaticTools::soundVolume);
		unmute();
	}
	catch (std::exception const& e) {
		//throw (std::runtime_error(e.what()));
		//StaticTools::Log << e.what() << std::endl;
		throw (std::runtime_error("menu: " + std::string(e.what())));
	}
}

void MainMenuController::addKeyAction(const sf::Keyboard::Key key, bool (MainMenuController::*func)(void)) {
	_keyActions.insert(std::make_pair(static_cast<uint32_t>(key), std::bind(func, this)));
}

void MainMenuController::buildKeyActionsMap(void) {
	addKeyAction(sf::Keyboard::Up, &MainMenuController::keyUp);
	addKeyAction(sf::Keyboard::PageUp, &MainMenuController::keyPageUp);
	addKeyAction(sf::Keyboard::Down, &MainMenuController::keyDown);
	addKeyAction(sf::Keyboard::PageDown, &MainMenuController::keyPageDown);
	addKeyAction(sf::Keyboard::Return, &MainMenuController::keyReturn);
}

bool MainMenuController::input(InputHandler &input)
{
	switch (_fsm) {
	case State::ST_Splash1:
	case State::ST_Splash2:
	case State::ST_Splash3:
	case State::ST_Splash4:
		return handleSplashInput(input);
	case State::ST_Menu:
		return handleMenuInput(input);
	case State::ST_Selecting:
		return handleSelectingInput(input);
	case State::ST_Username:
		return handleUsernamePopupInput(input);
	case State::ST_Creating:
		return handleCreatingInput(input);
	case State::ST_ConfirmCreate:
		return handleCreateConfirmPopupInput(input);
	case State::ST_Credits:
		return handleCreditsInput(input);
	case State::ST_Options:
		return handleOptionsInput(input);
	case State::ST_None:
	default:
		break;
	}
	return false;
}

bool MainMenuController::keyUp(void) {
	if (_action == (_buttons.begin()->getId()))
		_action = (--_buttons.end())->getId();
	else
		_action--;
	MainMenuResource::menuResourceManager.playSound(MainMenuResource::NAV_SOUND_1);
	return true;
}

bool MainMenuController::keyPageUp(void) {
	_action = _buttons.begin()->getId();
	MainMenuResource::menuResourceManager.playSound(MainMenuResource::NAV_SOUND_1);
	return true;
}

bool MainMenuController::keyDown(void) {
	if (_action == (--_buttons.end())->getId())
		_action = _buttons.begin()->getId();
	else
		_action++;
	MainMenuResource::menuResourceManager.playSound(MainMenuResource::NAV_SOUND_1);
	return true;
}

bool MainMenuController::keyPageDown(void) {
	_action = _buttons.rbegin()->getId();
	MainMenuResource::menuResourceManager.playSound(MainMenuResource::NAV_SOUND_1);
	return true;
}

bool MainMenuController::keyReturn(void) {
	switch (_action) {
	case SelectedAction::PLAY: {
		MainMenuResource::menuResourceManager.playSound(MainMenuResource::NAV_SOUND_2);
		_browser.clearContent();
		_client.write(std::make_shared<CMDGetParty>());
		_fsm = State::ST_Selecting;
		break;
	}
	case SelectedAction::QUIT: {
		_pushAction = SelectedAction::QUIT;
		break;
	}
	case SelectedAction::CREATE: {
		MainMenuResource::menuResourceManager.playSound(MainMenuResource::NAV_SOUND_2);
		_fsm = State::ST_Creating;
		break;
	}
	case SelectedAction::CREDITS: {
		MainMenuResource::menuResourceManager.playSound(MainMenuResource::NAV_SOUND_2);
		_fsm = State::ST_Credits;
		break;
	}
	case SelectedAction::OPTIONS: {
		MainMenuResource::menuResourceManager.playSound(MainMenuResource::NAV_SOUND_2);
		_optionsScreen.setHost(_connectData.hostIp);
		_optionsScreen.setPort(_connectData.port);
		_optionsScreen.setMusicValue(StaticTools::musicVolume);
		_optionsScreen.setSoundValue(StaticTools::soundVolume);
		_optionsScreen.resetFocus();
		_fsm = State::ST_Options;
		break;
	}
	case SelectedAction::NONE:
	default:
		break;
	}
	return true;
}

void MainMenuController::update(float delta)
{
	switch (_fsm) {
	case State::ST_Splash1:
		updateSplashFirstPhase(delta);
		break;
	case State::ST_Splash2:
		updateSplashSecondPhase(delta);
		break;
	case State::ST_Splash3:
		updateSplashThirdPhase(delta);
		break;
	case State::ST_Splash4:
		updateSplashFourthPhase(delta);
		break;
	case State::ST_Menu:
	case State::ST_Selecting:
	case State::ST_Username:
	case State::ST_Creating:
	case State::ST_ConfirmCreate:
	case State::ST_Credits:
	case State::ST_Options:
		updateMenu(delta);
		break;
	case State::ST_None:
	default:
		break;
	}
}

void MainMenuController::updateSplashFirstPhase(const float delta) {
	float pos = _titleSprites.begin()->getPosition().x - (delta * SPLASH_PX_PER_SEC);
	if (pos < SPLASH_TITLE_TARGET_POS)
		pos = static_cast<float>(SPLASH_TITLE_TARGET_POS);
	for (auto &sprite : _titleSprites) {
		sprite.setPosition(pos, static_cast<float>(TITLE_BASE_Y_POS));
	}
	if (_titleSprites.begin()->getPosition().x <= SPLASH_TITLE_TARGET_POS)
		_fsm = State::ST_Splash2;
}

void MainMenuController::updateSplashSecondPhase(const float delta) {
	float targetPos = static_cast<float>(SPLASH_TITLE_TARGET_POS);
	for (auto &sprite : _titleSprites) {
		float pos = sprite.getPosition().x + (delta * SPLASH_PX_PER_SEC);
		if (pos > targetPos)
			pos = targetPos;
		sprite.setPosition(pos, static_cast<float>(TITLE_BASE_Y_POS));
		targetPos += (sprite.getTextureRect().width * sprite.getScale().x) + TITLE_CHAR_SPACING;
	}
	sf::Sprite &last = *(--(_titleSprites.end()));
	if (last.getPosition().x >= targetPos - (last.getTextureRect().width * last.getScale().x) - TITLE_CHAR_SPACING)
		_fsm = State::ST_Splash3;
}

void MainMenuController::updateSplashThirdPhase(const float delta) {
	float pos = _titleSprites.begin()->getPosition().y + (delta * (SPLASH_PX_PER_SEC / 2));
	if (pos > TITLE_FINAL_Y_POS)
		pos = static_cast<float>(TITLE_FINAL_Y_POS);
	for (auto &sprite : _titleSprites) {
		sprite.setPosition(sprite.getPosition().x, pos);
	}
	if (_titleSprites.begin()->getPosition().y >= TITLE_FINAL_Y_POS) {
		_fsm = State::ST_Splash4;
	}
}

void MainMenuController::updateSplashFourthPhase(const float delta) {
	(void)delta;
	_fsm = State::ST_Menu;
	updateMenu(delta);
}

void MainMenuController::updateMenu(const float delta) {
	float pos = static_cast<float>(SPLASH_TITLE_TARGET_POS);
	for (auto &sprite : _titleSprites) {
		sprite.setPosition(pos, static_cast<float>(TITLE_FINAL_Y_POS));
		pos += (sprite.getTextureRect().width * sprite.getScale().x) + static_cast<float>(TITLE_CHAR_SPACING);
	}
	pos = BUTTON_Y_ORIGIN;
	for (auto &button : _buttons) {
		if (button.getId() == _action)
			button.setState(MenuButton::State::HOVERED);
		else
			button.setState(MenuButton::State::INACTIVE);
		button.setPosition(static_cast<float>(BUTTON_X_ALIGN), pos);
		pos += BUTTON_Y_SPACING;
	}
	_keyboardEventDelta += delta;
}

void MainMenuController::abortSplash(void) {
	_fsm = State::ST_Menu;
}

void MainMenuController::addBrowserEntry(GetParty const &data) {
	_browser.addEntry(data);
}

void MainMenuController::clearConnectData(void) {
	_connectData.game = "";
	_connectData.password = "";
	_connectData.password = "";
}

void MainMenuController::setHostIp(std::string const &hostIp) {
	_connectData.hostIp = hostIp;
}

void MainMenuController::setPort(std::string const &port) {
	_connectData.port = port;
}

void MainMenuController::setMusicVolume(const float volume) {
	ProjectResource::TheProjectResource.getMusicByKey(ProjectResource::MAIN_THEME).setVolume(volume);
}

void MainMenuController::setSoundVolume(const float volume) {
	MainMenuResource::menuResourceManager.getSoundByKey(MainMenuResource::NAV_SOUND_0)->setVolume(volume);
	MainMenuResource::menuResourceManager.getSoundByKey(MainMenuResource::NAV_SOUND_1)->setVolume(volume);
	MainMenuResource::menuResourceManager.getSoundByKey(MainMenuResource::NAV_SOUND_2)->setVolume(volume);
	MainMenuResource::menuResourceManager.getSoundByKey(MainMenuResource::NAV_SOUND_3)->setVolume(volume);
}

void MainMenuController::mute(void) const {
	ProjectResource::TheProjectResource.getMusicByKey(ProjectResource::MAIN_THEME).pause();
}

void MainMenuController::unmute(void) const {
	ProjectResource::TheProjectResource.getMusicByKey(ProjectResource::MAIN_THEME).setVolume(StaticTools::musicVolume);
	ProjectResource::TheProjectResource.getMusicByKey(ProjectResource::MAIN_THEME).setLoop(true);
	ProjectResource::TheProjectResource.getMusicByKey(ProjectResource::MAIN_THEME).play();
}

void MainMenuController::restartMusic(void) const {
	ProjectResource::TheProjectResource.getMusicByKey(ProjectResource::MAIN_THEME).stop();
	unmute();
}

void MainMenuController::draw(sf::RenderWindow &window)
{
	window.clear(sf::Color::Black);
 	for (auto &titleSprite : _titleSprites) {
		window.draw(titleSprite);
	}
	if (_fsm >= State::ST_Menu) {
		for (auto &button : _buttons) {
			window.draw(button);
		}
		if (_fsm == State::ST_Selecting || _fsm == State::ST_Username) {
			window.draw(_browser);
		}
		else if (_fsm == State::ST_Creating || _fsm == State::ST_ConfirmCreate) {
			window.draw(_form);
		}
		else if (_fsm == State::ST_Credits) {
			window.draw(_creditsScreen);
		}
		else if (_fsm == State::ST_Options) {
			window.draw(_optionsScreen);
		}
		if (_fsm == State::ST_ConfirmCreate) {
			window.draw(_confirmPopup);
		}
		else if (_fsm == State::ST_Username) {
			window.draw(_inputPopup);
		}
	}
}

void MainMenuController::recycle(void)
{
}

void MainMenuController::forceState(const State state) {
	_fsm = state;
	if (_fsm == State::ST_SplashStart) {
		for (auto &sprite : _titleSprites) {
			sprite.setPosition(static_cast<float>(SPLASH_INIT_POS), static_cast<float>(TITLE_BASE_Y_POS));
		}
	}
}

short MainMenuController::pullAction(void)
{
	short tmp = _pushAction;
	_pushAction = SelectedAction::NONE;
	return (tmp);
}

MainMenuController::ConnectData const &MainMenuController::getConnectData(void) const {
	return _connectData;
}

bool MainMenuController::handleCreatingInput(InputHandler &input) {
	if (_keyboardEventDelta >= KEYBOARD_EVENT_DELTA_MIN) {
		if (input.isKeyDown(sf::Keyboard::Escape)) {
			_fsm = State::ST_Menu;
			_keyboardEventDelta = 0.f;
			return true;
		}
		else if (input.isKeyDown(sf::Keyboard::Return) && _form.getFocusedField() + 1 == _form.getFieldCount()) {
			try {
				_connectData.game = _form.getFieldContent(FORM_GAME_NAME);
				_connectData.password = _form.getFieldContent(FORM_PASSWORD);
				_connectData.username = _form.getFieldContent(FORM_PLAYER_NAME);
				_fsm = State::ST_ConfirmCreate;
				_confirmPopup.setConfirmed(true);
			}
			catch (std::runtime_error const &e) {
				std::cout << e.what() << std::endl;
			}
			_keyboardEventDelta = 0.f;
			_form.setFocusedField(0);
			return true;
		}
		else if (_form.input(input)) {
			_keyboardEventDelta = 0.f;
			return true;
		}
	}
	return false;
}

bool MainMenuController::handleCreateConfirmPopupInput(InputHandler &input) {
	if (_keyboardEventDelta >= KEYBOARD_EVENT_DELTA_MIN) {
		if (input.isKeyDown(sf::Keyboard::Return)) {
			_keyboardEventDelta = 0.f;
			if (_confirmPopup.isConfirmed()) {
				_client.write(std::make_shared<CMDCreateParty>(_connectData.game, _connectData.password));
				_pushAction = SelectedAction::CREATE;
				_fsm = State::ST_Menu;
			}
			else {
				_fsm = State::ST_Creating;
			}
			return true;
		}
		else if (input.isKeyDown(sf::Keyboard::Escape)) {
			_keyboardEventDelta = 0.f;
			_fsm = State::ST_Creating;
			return true;
		}
		if (_confirmPopup.input(input)) {
			_keyboardEventDelta = 0.f;
			return true;
		}
	}
	return false;
}

bool MainMenuController::handleSelectingInput(InputHandler &input) {
	if (_keyboardEventDelta >= KEYBOARD_EVENT_DELTA_MIN) {
		if (input.isKeyDown(sf::Keyboard::Escape) || input.isKeyDown(sf::Keyboard::Right)) {
			_fsm = State::ST_Menu;
			_keyboardEventDelta = 0.f;
			return true;
		}
		else if (input.isKeyDown(sf::Keyboard::F5)) {
			_browser.clearContent();
			_client.write(std::make_shared<CMDGetParty>());
		}
		else if (input.isKeyDown(sf::Keyboard::Return) && _browser.getContent().size() > 0) {
			_selectedServer = _browser.getSelected();
			_connectData.game = _browser.getContent().at(_selectedServer).name;
			_fsm = State::ST_Username;
			_inputPopup.removeFields();
			_inputPopup.addField("Username", _connectData.username);
			if (_browser.getContent().at(_selectedServer).hasPassword) {
				_inputPopup.addField("Password");
			}
			_inputPopup.resizeAndCenter();
			_keyboardEventDelta = 0.f;
			return true;
		}
		else if (_browser.input(input)) {
			_keyboardEventDelta = 0.f;
			return true;
		}
	}
	return false;
}

bool MainMenuController::handleUsernamePopupInput(InputHandler &input) {
	if (_keyboardEventDelta >= KEYBOARD_EVENT_DELTA_MIN) {
		if (input.isKeyDown(sf::Keyboard::Return) && _inputPopup.getForm().getFocusedField() == _inputPopup.getForm().getFieldCount() - 1) {
			_keyboardEventDelta = 0.f;
			try {
				_connectData.username = _inputPopup.getTextFieldContent("Username");
				if (_connectData.username.empty())
					_connectData.username = FORM_PLAYER_NAME_DEFAULT;
				_connectData.password = _inputPopup.getTextFieldContent("Password");
			}
			catch (std::runtime_error const &) {

			}
			_pushAction = SelectedAction::PLAY;
			_fsm = State::ST_Menu;
			return true;
		}
		else if (input.isKeyDown(sf::Keyboard::Escape)) {
			_keyboardEventDelta = 0.f;
			_fsm = State::ST_Selecting;
			return true;
		}
		if (_inputPopup.input(input)) {
			_keyboardEventDelta = 0.f;
			return true;
		}
	}
	return false;
}

bool MainMenuController::handleMenuInput(InputHandler &input) {
	if (_keyboardEventDelta >= KEYBOARD_EVENT_DELTA_MIN) {
		for (auto &keyAction : _keyActions) {
			if (input.isKeyDown(static_cast<sf::Keyboard::Key>(keyAction.first))) {
				_keyboardEventDelta = 0.f;
				return keyAction.second();
			}
		}
	}
	return false;
}

bool MainMenuController::handleSplashInput(InputHandler &input) {
	if (input.isKeyDown(sf::Keyboard::Space) || input.isKeyDown(sf::Keyboard::Return)) {
		abortSplash();
		return true;
	}
	return false;
}

bool MainMenuController::handleCreditsInput(InputHandler & input) {
	if (_keyboardEventDelta >= KEYBOARD_EVENT_DELTA_MIN) {
		if (input.isKeyDown(sf::Keyboard::Escape) ||
			input.isKeyDown(sf::Keyboard::Return) ||
			input.isKeyDown(sf::Keyboard::Right)) {
			_fsm = State::ST_Menu;
			_keyboardEventDelta = 0.f;
			return true;
		}
		else if (input.isKeyDown(sf::Keyboard::Up) || input.isKeyDown(sf::Keyboard::Down)) {
			_fsm = State::ST_Menu;
			return handleMenuInput(input);
		}
	}
	return false;
}

bool MainMenuController::handleOptionsInput(InputHandler &input) {
	if (_keyboardEventDelta >= KEYBOARD_EVENT_DELTA_MIN) {
		if (input.isKeyDown(sf::Keyboard::Escape)) {
			_fsm = State::ST_Menu;
			_keyboardEventDelta = 0.f;
			return true;
		}
		else if (input.isKeyDown(sf::Keyboard::Return) && _optionsScreen.getFocusedItem() == MenuOptions::FocusedItem::MUSIC_SLIDER) {
			_fsm = State::ST_Menu;
			_keyboardEventDelta = 0.f;
			StaticTools::musicVolume = _optionsScreen.getMusicValue();
			StaticTools::soundVolume = _optionsScreen.getSoundValue();
			setMusicVolume(StaticTools::musicVolume);
			setSoundVolume(StaticTools::soundVolume);
			_connectData.hostIp = _optionsScreen.getHost();
			_connectData.port = _optionsScreen.getPort();
			_pushAction = SelectedAction::OPTIONS;
			return true;
		}
		else if (_optionsScreen.input(input)) {
			setMusicVolume(StaticTools::musicVolume);
			setSoundVolume(StaticTools::soundVolume);
			_keyboardEventDelta = 0.f;
		}
	}
	return false;
}
