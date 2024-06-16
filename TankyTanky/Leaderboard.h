#pragma once


#include "BackButton.h"
#include "Game.h"
#include "NextButton.h"


class Leaderboard
{
public:

	Leaderboard() = default;

	~Leaderboard() = default;

	void createPage(Page& page, const std::vector<std::pair<int, PlayerInfo>>& data, float start_index, float results_per_page, sf::RenderWindow& window);

	void runLeaderboard(std::vector<std::unique_ptr<Button>>& buttons, sf::RectangleShape& border, const sf::Event& event, sf::RenderWindow& window);

	static int leaderboard_guard;
};
