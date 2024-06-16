#pragma once



#include "Collision.h"
#include "HeavyTankEnemy.h"
#include "LightTankEnemy.h"
#include "MediumTankEnemy.h"
#include "Menu.h"


class Game
{
public:

	Game();

	~Game() = default;

	void runGame();

	static std::vector<std::pair<int, PlayerInfo>> readFromFile();

private:

	static void writeToFile(const std::vector<std::pair<int, PlayerInfo>>& data);

	void writeStatistics(sf::RenderWindow& window);

	static void spawnEnemies(std::vector<std::unique_ptr<TankEnemy>>& enemies, sf::RenderWindow& window);

	void endGame();

	static std::string getCurrentDate();

	std::string countTime();

	std::vector<std::unique_ptr<sf::RenderWindow>> window;

	bool is_game_over;

	static sf::Clock game_clock;

	static std::string final_game_time;

};

