#include "MainMenuController.hpp"
#include "MainMenuResource.hpp"

const uint32_t MainMenuController::BUTTON_Y_SPACING = 45;
const uint32_t MainMenuController::BUTTON_Y_ORIGIN = 50;
const uint32_t MainMenuController::BUTTON_X_ALIGN = StaticTools::GetResolution().first - 190;
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

MainMenuController::MainMenuController()
  : _fsm(State::ST_SplashStart), _action(SelectedAction::NONE), _keyboardEventDelta(0.f), _pushAction(SelectedAction::NONE)
{
	MainMenuResource::menuResourceManager.load();
	buildKeyActionsMap();
}

MainMenuController::~MainMenuController(void)
{
}

void MainMenuController::init()
{
	try {
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
		_buttons.push_back(MenuButton("Play", static_cast<short>(SelectedAction::PLAY), &ProjectResource::TheProjectResource.getFontByKey(ProjectResource::MAIN_FONT)));
		_buttons.push_back(MenuButton("Quit", static_cast<short>(SelectedAction::QUIT), &ProjectResource::TheProjectResource.getFontByKey(ProjectResource::MAIN_FONT)));
		_action = SelectedAction::PLAY;
		//unmute();		
		_fsm = State::ST_Splash1;
	}
	catch (std::exception const& e) {
		throw (std::runtime_error(e.what()));
	}
}

void MainMenuController::addKeyAction(const sf::Keyboard::Key key, bool (MainMenuController::*func)(void)) {
	_keyActions.insert(std::make_pair(static_cast<uint32_t>(key), std::bind(func, this)));
}

void MainMenuController::buildKeyActionsMap(void) {
	addKeyAction(sf::Keyboard::Up, &MainMenuController::keyUp);
	addKeyAction(sf::Keyboard::Down, &MainMenuController::keyDown);
	addKeyAction(sf::Keyboard::Return, &MainMenuController::keyReturn);
}

bool MainMenuController::input(InputHandler &input)
{
	if (_fsm == State::ST_Splash1 || _fsm == State::ST_Splash2 || _fsm == State::ST_Splash3) {
		if (input.isKeyDown(sf::Keyboard::Space) || input.isKeyDown(sf::Keyboard::Return)) {
			abortSplash();
			return true;
		}
	}
	else if (_fsm == State::ST_Menu) {
		if (_keyboardEventDelta >= KEYBOARD_EVENT_DELTA_MIN) {
			for (auto &keyAction : _keyActions) {
				if (input.isKeyDown(static_cast<sf::Keyboard::Key>(keyAction.first))) {
					_keyboardEventDelta = 0.f;
					return keyAction.second();
				}
			}
		}
	}
	return (false);
}

bool MainMenuController::keyUp(void) {
	if (_action == (_buttons.begin()->getId()))
		_action = (--_buttons.end())->getId();
	else
		_action--;
	return true;
}

bool MainMenuController::keyDown(void) {
	if (_action == (--_buttons.end())->getId())
		_action = _buttons.begin()->getId();
	else
		_action++;
	return true;
}

bool MainMenuController::keyReturn(void) {
	switch (_action) {
	case SelectedAction::PLAY: {
		std::cout << "Play" << std::endl;
		_pushAction = SelectedAction::PLAY;
		break;
	}
	case SelectedAction::QUIT: {
		std::cout << "Quit" << std::endl;
		_pushAction = SelectedAction::QUIT;
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
	case State::ST_Menu:
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
		_fsm = State::ST_Menu;
	}
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

void MainMenuController::mute(void) const {
	ProjectResource::TheProjectResource.getMusicByKey(ProjectResource::MAIN_THEME).pause();
}

void MainMenuController::unmute(void) const {
	ProjectResource::TheProjectResource.getMusicByKey(ProjectResource::MAIN_THEME).play();
}

void MainMenuController::draw(sf::RenderWindow &window)
{
	window.clear(sf::Color::Black);
 	for (auto &titleSprite : _titleSprites) {
		window.draw(titleSprite);
	}
	if (_fsm == State::ST_Menu) {
		for (auto &button : _buttons) {
			window.draw(button);
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
