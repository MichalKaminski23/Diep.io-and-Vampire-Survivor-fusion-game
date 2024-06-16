#include "TankEnemy.h"


int TankEnemy::wave_count = 0;
int TankEnemy::enemies_left = 0;
int TankEnemy::enemies_killed = 0;
int TankEnemy::sum_enemies_bullets = 0;


void TankEnemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->tank_enemy);
}


bool TankEnemy::isAlive() const
{
	return alive;
}


void TankEnemy::kill()
{
	alive = false;
}


void TankEnemy::moveEnemies(std::vector<std::unique_ptr<TankEnemy>>& enemies, const float& dt)
{
	for (auto& enemy : enemies)
	{
		sf::Vector2f velocity = enemy->calculateEnemiesVelocity();
		enemy->tank_enemy.move(velocity * dt);
	}
}


void TankEnemy::shootPlayer(std::vector<std::unique_ptr<TankEnemy>>& enemies, sf::RenderWindow& window)
{
	for (auto& enemy : enemies)
	{
		enemy->shoot(window);
	}
}


sf::Vector2f TankEnemy::getPlayerPosition() const
{
	return TankPlayer::tank_player.getPosition();
}


sf::Vector2f TankEnemy::getEnemyPosition() const
{
	return tank_enemy.getPosition();
}



