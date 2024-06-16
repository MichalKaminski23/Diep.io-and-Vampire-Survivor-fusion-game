#pragma once


#include "Button.h"


class TextBox : public Button
{
public:

	using Button::Button;

	void clearTextBox();

	static bool text_check;

	static std::string input_text;

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual void onClick(const sf::Event& event, sf::RenderWindow& window) override;

	int guard = 0;

};

