#pragma once


#include "Author.h"
#include "Leaderboard.h"
#include "NewGame.h"


class Menu
{
public:

	Menu();

	~Menu() = default;

	void runMenu();

private:

	std::vector<std::unique_ptr<sf::RenderWindow>> window;

};

