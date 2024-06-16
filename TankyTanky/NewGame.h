#pragma once


#include "Game.h"
#include "TextBox.h"


class NewGame
{
public:

	NewGame() = default;

	~NewGame() = default;

	void runNewGame(std::vector<std::unique_ptr<Button>>& buttons, sf::RectangleShape& border, TextBox& text_box, const sf::Event& event, sf::RenderWindow& window);

};

