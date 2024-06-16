#include "LightTankEnemy.h"


LightTankEnemy::LightTankEnemy(const int& point_count, const float& x, const float& y, const sf::Color& color)
{
	tank_enemy.setPosition(x, y);
	tank_enemy.setRadius(25);
	tank_enemy.setPointCount(point_count);
	tank_enemy.setOutlineThickness(3);
	tank_enemy.setOutlineColor(sf::Color::Black);
	tank_enemy.setFillColor(color);

	enemy_health = 1.f;
	enemy_bullet_damage = 0.5f;
	enemy_body_damage = 0.5f;
}


sf::Vector2f LightTankEnemy::calculateEnemiesVelocity()
{
	sf::Vector2f enemy_position = getEnemyPosition();
	sf::Vector2f player_position = getPlayerPosition();

	sf::Vector2f direction = player_position - enemy_position;
	float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (distance != 0)
	{
		direction /= distance;
	}

	float speed = 150.f;

	sf::Vector2f velocity = direction * speed;

	return velocity;
}


void LightTankEnemy::shoot(sf::RenderWindow& window)
{
	Other::writingText(TankEnemy::getEnemyPosition().x + 21, TankEnemy::getEnemyPosition().y + 10, 20, 1, "L", sf::Color::White, sf::Color::Black, sf::Text::Regular, window);

	if (clock.getElapsedTime().asSeconds() > static_cast<float>(rand() % 3 + 1))
	{
		auto bullet = std::make_unique<sf::CircleShape>();
		bullet->setRadius(3);
		bullet->setFillColor(sf::Color::Magenta);
		bullet->setPointCount(3);
		bullet->setPosition(getEnemyPosition().x + 20, getEnemyPosition().y + 20);
		bullet->setOutlineColor(sf::Color::Black);
		bullet->setOutlineThickness(2);

		float angle = atan2(TankPlayer::tank_player.getPosition().y - getEnemyPosition().y,
			TankPlayer::tank_player.getPosition().x - getEnemyPosition().x);

		enemy_bullets.push_back(std::move(bullet));
		enemy_angles.push_back(angle);

		TankEnemy::sum_enemies_bullets++;

		clock.restart();
	}

	for (int i = 0; i < enemy_bullets.size(); i++)
	{
		enemy_bullets[i]->move(5 * cos(enemy_angles[i]), 5 * sin(enemy_angles[i]));
		window.draw(*enemy_bullets[i]);
	}
}

