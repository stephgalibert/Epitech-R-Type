#pragma once

#include "MenuPopup.hpp"
#include "MenuButton.hpp"

class MenuConfirmPopup : public MenuPopup {
	static const std::string CONFIRM_BUTTON_LABEL_DEFAULT;
	static const std::string CANCEL_BUTTON_LABEL_DEFAULT;
	static const float MESSAGE_LATERAL_PADDING;
	static const float MESSAGE_VERTICAL_PADDING;
	static const uint32_t BUTTON_FONT_SIZE;

public:
	MenuConfirmPopup(const bool screenCover = true);
	virtual ~MenuConfirmPopup();

public:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual bool input(InputHandler &input);
	virtual void updateDisplay(void);

public:
	virtual void setPosition(sf::Vector2f const &position);
	virtual void setSize(sf::Vector2f const &size);
	virtual void setFont(sf::Font const *font);
	void setMessage(std::string const &message);
	void setConfirmButtonLabel(std::string const &label);
	void setCancelButtonLabel(std::string const &label);
	void setConfirmed(const bool confirmed);

public:
	bool isConfirmed(void) const;

private:
	sf::Text _message;
	MenuButton _confirmButton;
	MenuButton _cancelButton;
};