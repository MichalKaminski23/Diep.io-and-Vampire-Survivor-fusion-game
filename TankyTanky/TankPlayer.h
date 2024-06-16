#pragma once


#include "TankEnemy.h"


class TankPlayer
{
public:

	TankPlayer() = default;

	~TankPlayer() = default;

	static void moveTank(sf::Clock clock, sf::Time delta_time, float dt, sf::RenderWindow& window);

	static void shootBullet(sf::RenderWindow& window);

	static int getTankPlayerColor();

	static int getTankPlayerFigure();

	static void playerUpgrade(sf::RenderWindow& window, const sf::Event& event);

	static float player_health;

	static float player_max_health;

	static float player_speed;

	static float player_body_damage;

	static float player_bullet_damage;

	static float player_bullet_delay;

	static float player_bullet_speed;

	static int sum_player_bullets;

	static bool pause;

	static bool upgrade_selected;

	static std::vector<float> player_angles;

	static std::vector<std::unique_ptr<sf::CircleShape>> player_bullets;

	static sf::CircleShape tank_player;


private:

	static int color_number;

	static int figure_number;

};
