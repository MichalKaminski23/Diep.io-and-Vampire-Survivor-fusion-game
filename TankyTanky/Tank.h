#pragma once


#include "TankPlayer.h"
#include "Button.h"


class Tank : public Button
{
public:

	using Button::Button;

	void changeColor(const sf::Color& color);

	sf::Color getTankColor();

	static bool figure_check;

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual void onClick(const sf::Event& event, sf::RenderWindow& window) override;

};

