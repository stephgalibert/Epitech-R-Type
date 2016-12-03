#include "MainMenuController.hpp"
#include "MainMenuResource.hpp"

const uint32_t MainMenuController::TITLE_BASE_Y_POS = 100;
const uint32_t MainMenuController::TITLE_FINAL_Y_POS = 280;
const uint32_t MainMenuController::TITLE_CHAR_SPACING = 10;
const uint32_t MainMenuController::SPLASH_PX_PER_SEC = 800 / 1.5;
const uint32_t MainMenuController::SPLASH_INIT_POS = 800;
const uint32_t MainMenuController::SPLASH_TITLE_TARGET_POS = 35;

MainMenuController::MainMenuController()
	: _fsm(State::ST_Splash1)
{
	MainMenuResource::menuResourceManager.load();
}

MainMenuController::~MainMenuController(void)
{
}

void MainMenuController::init(void)
{
	try {
		_titleSprites.push_back(sf::Sprite(*MainMenuResource::menuResourceManager.getTextureByKey(MainMenuResource::LOGO_R)));
		_titleSprites.push_back(sf::Sprite(*MainMenuResource::menuResourceManager.getTextureByKey(MainMenuResource::LOGO_DOT)));
		_titleSprites.push_back(sf::Sprite(*MainMenuResource::menuResourceManager.getTextureByKey(MainMenuResource::LOGO_T)));
		_titleSprites.push_back(sf::Sprite(*MainMenuResource::menuResourceManager.getTextureByKey(MainMenuResource::LOGO_Y)));
		_titleSprites.push_back(sf::Sprite(*MainMenuResource::menuResourceManager.getTextureByKey(MainMenuResource::LOGO_P)));
		_titleSprites.push_back(sf::Sprite(*MainMenuResource::menuResourceManager.getTextureByKey(MainMenuResource::LOGO_E)));
		for (auto &sprite : _titleSprites) {
			sprite.setScale(2.f, 2.f);
			sprite.setPosition(SPLASH_INIT_POS, TITLE_BASE_Y_POS);
		}
		ProjectResource::TheProjectResource.getMusicByKey(ProjectResource::MAIN_THEME).play();
		_fsm = State::ST_Splash1;
	}
	catch (std::exception const& e) {
		throw (std::runtime_error(e.what()));
	}
}

bool MainMenuController::input(InputHandler &input)
{
	if (_fsm == State::ST_Splash1 || _fsm == State::ST_Splash2 || _fsm == State::ST_Splash3) {
		if (input.isKeyDown(sf::Keyboard::Space) || input.isKeyDown(sf::Keyboard::Return))
			abortSplash();
	}
	return (false);
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
		updateMenu();
		break;
	case State::ST_None:
	default:
		break;
	}
}

void MainMenuController::updateSplashFirstPhase(const float delta) {
	float pos = _titleSprites.begin()->getPosition().x - (delta * SPLASH_PX_PER_SEC);
	if (pos < SPLASH_TITLE_TARGET_POS)
		pos = SPLASH_TITLE_TARGET_POS;
	for (auto &sprite : _titleSprites) {
		sprite.setPosition(pos, TITLE_BASE_Y_POS);
	}
	if (_titleSprites.begin()->getPosition().x <= SPLASH_TITLE_TARGET_POS)
		_fsm = State::ST_Splash2;
}

void MainMenuController::updateSplashSecondPhase(const float delta) {
	uint32_t targetPos = SPLASH_TITLE_TARGET_POS;
	for (auto &sprite : _titleSprites) {
		uint32_t pos = sprite.getPosition().x + (delta * SPLASH_PX_PER_SEC);
		if (pos > targetPos)
			pos = targetPos;
		sprite.setPosition(pos, TITLE_BASE_Y_POS);
		targetPos += (sprite.getTextureRect().width * sprite.getScale().x) + TITLE_CHAR_SPACING;
	}
	sf::Sprite &last = *(--(_titleSprites.end()));
	if (last.getPosition().x >= targetPos - (last.getTextureRect().width * last.getScale().x) - TITLE_CHAR_SPACING)
		_fsm = State::ST_Splash3;
}

void MainMenuController::updateSplashThirdPhase(const float delta) {
	uint32_t pos = _titleSprites.begin()->getPosition().y + (delta * (SPLASH_PX_PER_SEC / 2));
	if (pos > TITLE_FINAL_Y_POS)
		pos = TITLE_FINAL_Y_POS;
	for (auto &sprite : _titleSprites) {
		sprite.setPosition(sprite.getPosition().x, pos);
	}
	if (_titleSprites.begin()->getPosition().y >= TITLE_FINAL_Y_POS) {
		_fsm = State::ST_Menu;
	}
}

void MainMenuController::updateMenu(void) {
	uint32_t pos = SPLASH_TITLE_TARGET_POS;
	for (auto &sprite : _titleSprites) {
		sprite.setPosition(pos, TITLE_FINAL_Y_POS);
		pos += (sprite.getTextureRect().width * sprite.getScale().x) + TITLE_CHAR_SPACING;
	}
}

void MainMenuController::abortSplash(void) {
	_fsm = State::ST_Menu;
}

void MainMenuController::draw(sf::RenderWindow &window)
{
	for (auto &titleSprite : _titleSprites) {
		window.draw(titleSprite);
	}
}

void MainMenuController::recycle(void)
{
}
