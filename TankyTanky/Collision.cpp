#include "Collision.h"


Collision::Collision(const float& x, const float& y)
{
	border.setSize(sf::Vector2f(x, y));
	border.setFillColor(sf::Color::Transparent);
	border.setOutlineThickness(2);
	border.setOutlineColor(sf::Color::Black);
	border.setPosition(2, 2);
}


Collision::Collision(const float& x, const float& y, const float& size, Direction direction)
{
	vertical.setSize(sf::Vector2f(size / 5, size * 2));
	vertical.setFillColor(sf::Color::Black);
	vertical.setRotation(0);

	horizontal.setSize(sf::Vector2f(size, size / 5));
	horizontal.setFillColor(sf::Color::Black);
	horizontal.setRotation(180);

	switch (direction)
	{
	case Direction::LT:
		vertical.setPosition(x, y);
		horizontal.setPosition(x + size + 20, y + 20);
		break;

	case Direction::LB:
		vertical.setPosition(x, y);
		horizontal.setPosition(x, y + size / 5);
		break;

	case Direction::RT:
		vertical.setPosition(x, y + size / 5);
		horizontal.setPosition(x + size + 20, y + size + size + 20);
		break;

	case Direction::RB:
		vertical.setPosition(x, y + size / 5);
		horizontal.setPosition(x, y + size + size + 20);
		break;
	}
}


void Collision::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->border);
	target.draw(this->vertical);
	target.draw(this->horizontal);
}


void Collision::verticalCollision(std::vector<std::unique_ptr<TankEnemy>>& enemies) const
{
	sf::FloatRect player_bounds = TankPlayer::tank_player.getGlobalBounds();
	sf::FloatRect vertical_bounds = vertical.getGlobalBounds();

	//Player's collision with vertical objects
	if (player_bounds.intersects(vertical_bounds))
	{
		if (player_bounds.left < vertical_bounds.left - 22)
		{
			TankPlayer::tank_player.setPosition(vertical_bounds.left - 40, TankPlayer::tank_player.getPosition().y);
		}
		else if (player_bounds.left + 22 < vertical_bounds.left + vertical_bounds.width + 35)
		{
			TankPlayer::tank_player.setPosition(vertical_bounds.left + vertical_bounds.width + 35, TankPlayer::tank_player.getPosition().y);
		}
	}

	//Enemies' collision with vertical objects
	for (auto& enemy : enemies)
	{
		sf::FloatRect enemy_bounds = enemy->tank_enemy.getGlobalBounds();

		if (enemy_bounds.intersects(vertical_bounds))
		{
			if (enemy_bounds.left < vertical_bounds.left - 22)
			{
				enemy->tank_enemy.setPosition(vertical_bounds.left - 55, enemy->tank_enemy.getPosition().y);
			}
			else if (enemy_bounds.left + 22 < vertical_bounds.left + vertical_bounds.width + 35)
			{
				enemy->tank_enemy.setPosition(vertical_bounds.left + vertical_bounds.width + 10, enemy->tank_enemy.getPosition().y);
			}
		}
	}
}


void Collision::horizontalCollision(std::vector<std::unique_ptr<TankEnemy>>& enemies) const
{
	sf::FloatRect player_bounds = TankPlayer::tank_player.getGlobalBounds();
	sf::FloatRect horizontal_bounds = horizontal.getGlobalBounds();

	//Player's collision with horizontal objects
	if (player_bounds.intersects(horizontal_bounds))
	{
		if (player_bounds.top < horizontal_bounds.top - 24)
		{
			TankPlayer::tank_player.setPosition(TankPlayer::tank_player.getPosition().x, horizontal_bounds.top - 40);
		}
		else if (player_bounds.top + 24 < horizontal_bounds.top + horizontal_bounds.height + 45)
		{
			TankPlayer::tank_player.setPosition(TankPlayer::tank_player.getPosition().x, horizontal_bounds.top + horizontal_bounds.height + 45);
		}
	}

	//Enemies' collision with horizontal objects
	for (auto& enemy : enemies)
	{
		sf::FloatRect enemy_bounds = enemy->tank_enemy.getGlobalBounds();

		if (enemy_bounds.intersects(horizontal_bounds))
		{
			if (enemy_bounds.top < horizontal_bounds.top)
			{
				enemy->tank_enemy.setPosition(enemy->tank_enemy.getPosition().x, horizontal_bounds.top - enemy_bounds.height - 5);
			}
			else if (enemy_bounds.top + enemy_bounds.height > horizontal_bounds.top + horizontal_bounds.height)
			{
				enemy->tank_enemy.setPosition(enemy->tank_enemy.getPosition().x, horizontal_bounds.top + horizontal_bounds.height + 5);
			}
		}
	}
}


void Collision::borderCollision(std::vector<std::unique_ptr<TankEnemy>>& enemies) const
{
	sf::Vector2f border_position = border.getPosition();

	//Player's collision with border
	//right
	if (TankPlayer::tank_player.getPosition().x > border_position.x + 1164)
	{
		TankPlayer::tank_player.setPosition(border_position.x + 1164, TankPlayer::tank_player.getPosition().y);
	}
	//left
	if (TankPlayer::tank_player.getPosition().x < border_position.x + 32)
	{
		TankPlayer::tank_player.setPosition(border_position.x + 32, TankPlayer::tank_player.getPosition().y);
	}
	//top
	if (TankPlayer::tank_player.getPosition().y < border_position.y + 32)
	{
		TankPlayer::tank_player.setPosition(TankPlayer::tank_player.getPosition().x, border_position.y + 32);
	}
	//bottom
	if (TankPlayer::tank_player.getPosition().y > border_position.y + 964)
	{
		TankPlayer::tank_player.setPosition(TankPlayer::tank_player.getPosition().x, border_position.y + 964);
	}

	//Enemies' collision with border
	for (auto& enemy : enemies)
	{
		//right
		if (enemy->tank_enemy.getPosition().x > border_position.x + 1140)
		{
			enemy->tank_enemy.setPosition(border_position.x + 1140, enemy->tank_enemy.getPosition().y);
		}
		//left
		if (enemy->tank_enemy.getPosition().x < border_position.x + 8)
		{
			enemy->tank_enemy.setPosition(border_position.x + 8, enemy->tank_enemy.getPosition().y);
		}
		//top
		if (enemy->tank_enemy.getPosition().y < border_position.y + 8)
		{
			enemy->tank_enemy.setPosition(enemy->tank_enemy.getPosition().x, border_position.y + 8);
		}
		//bottom
		if (enemy->tank_enemy.getPosition().y > border_position.y + 944)
		{
			enemy->tank_enemy.setPosition(enemy->tank_enemy.getPosition().x, border_position.y + 944);
		}
	}
}


void Collision::bulletColliion(std::vector<std::unique_ptr<TankEnemy>>& enemies) const
{
	sf::Vector2f border_position = border.getPosition();
	sf::FloatRect horizontal_bounds = horizontal.getGlobalBounds();
	sf::FloatRect vertical_bounds = vertical.getGlobalBounds();

	//Player's bullets collision with border or other objects
	for (int i = 0; i < TankPlayer::player_bullets.size(); ++i)
	{
		if (TankPlayer::player_bullets[i]->getPosition().x > 1200 or
			TankPlayer::player_bullets[i]->getPosition().x < border_position.x or
			TankPlayer::player_bullets[i]->getPosition().y < border_position.y or
			TankPlayer::player_bullets[i]->getPosition().y > 1000)
		{
			TankPlayer::player_bullets.erase(TankPlayer::player_bullets.begin() + i);
			TankPlayer::player_angles.erase(TankPlayer::player_angles.begin() + i);

			--i;
		}

		else if (TankPlayer::player_bullets[i]->getGlobalBounds().intersects(horizontal_bounds) or
			TankPlayer::player_bullets[i]->getGlobalBounds().intersects(vertical_bounds))
		{
			TankPlayer::player_bullets.erase(TankPlayer::player_bullets.begin() + i);
			TankPlayer::player_angles.erase(TankPlayer::player_angles.begin() + i);

			--i;
		}
	}

	//Enemies' bullets collision with border or other objects
	for (auto& enemy : enemies)
	{
		for (int i = 0; i < enemy->enemy_bullets.size(); ++i)
		{
			if (enemy->enemy_bullets[i]->getPosition().x > 1200 or
				enemy->enemy_bullets[i]->getPosition().x < border_position.x or
				enemy->enemy_bullets[i]->getPosition().y < border_position.y or
				enemy->enemy_bullets[i]->getPosition().y > 1000)
			{
				enemy->enemy_bullets.erase(enemy->enemy_bullets.begin() + i);
				enemy->enemy_angles.erase(enemy->enemy_angles.begin() + i);

				--i;
			}

			else if (enemy->enemy_bullets[i]->getGlobalBounds().intersects(horizontal_bounds) or
				enemy->enemy_bullets[i]->getGlobalBounds().intersects(vertical_bounds))
			{
				enemy->enemy_bullets.erase(enemy->enemy_bullets.begin() + i);
				enemy->enemy_angles.erase(enemy->enemy_angles.begin() + i);

				--i;
			}
		}
	}
}


void Collision::detectEnemyCollisions(std::vector<std::unique_ptr<TankEnemy>>& enemies) const
{
	std::vector<int> dead_enemies_indices;

	for (auto it = enemies.begin(); it != enemies.end(); ++it)
	{
		auto& enemy = *it;

		//Enemies' collision with Player's bullets
		for (int i = 0; i < TankPlayer::player_bullets.size(); ++i)
		{
			if (TankPlayer::player_bullets[i]->getGlobalBounds().intersects(enemy->tank_enemy.getGlobalBounds()))
			{
				TankPlayer::player_bullets.erase(TankPlayer::player_bullets.begin() + i);
				TankPlayer::player_angles.erase(TankPlayer::player_angles.begin() + i);
				--i;

				enemy->TankEnemy::enemy_health -= TankPlayer::player_bullet_damage;

				if (enemy->TankEnemy::enemy_health <= 0)
				{
					enemy->kill();
					dead_enemies_indices.push_back(std::distance(enemies.begin(), it));

					--TankEnemy::enemies_left;
					++TankEnemy::enemies_killed;
				}
			}
		}

		//Player's collision with Enemies' bullets
		for (int i = 0; i < enemy->enemy_bullets.size(); ++i)
		{
			if (enemy->enemy_bullets[i]->getGlobalBounds().intersects(TankPlayer::tank_player.getGlobalBounds()))
			{
				enemy->enemy_bullets.erase(enemy->enemy_bullets.begin() + i);
				enemy->enemy_angles.erase(enemy->enemy_angles.begin() + i);
				--i;
				TankPlayer::player_health -= enemy->enemy_bullet_damage;
			}
		}

		//Enemies' collision with Player's shape
		if (TankPlayer::tank_player.getGlobalBounds().intersects(enemy->tank_enemy.getGlobalBounds())
			or enemy->tank_enemy.getGlobalBounds().intersects(TankPlayer::tank_player.getGlobalBounds()))
		{
			TankPlayer::player_health -= enemy->enemy_body_damage;
			enemy->enemy_health -= TankPlayer::player_body_damage;

			TankPlayer::tank_player.setPosition(TankPlayer::tank_player.getPosition().x, TankPlayer::tank_player.getPosition().y);
			enemy->tank_enemy.setPosition(enemy->tank_enemy.getPosition().x + 50, enemy->tank_enemy.getPosition().y + 50);

			if (enemy->TankEnemy::enemy_health <= 0)
			{
				enemy->kill();
				dead_enemies_indices.push_back(std::distance(enemies.begin(), it));
				--TankEnemy::enemies_left;
				++TankEnemy::enemies_killed;
			}
		}
	}

	for (auto it = dead_enemies_indices.rbegin(); it != dead_enemies_indices.rend(); ++it)
	{
		enemies.erase(enemies.begin() + *it);
	}
}


void Collision::enemiesSelfCollisions(std::vector<std::unique_ptr<TankEnemy>>& enemies) const
{
	for (auto& enemy1 : enemies)
	{
		for (auto& enemy2 : enemies)
		{
			if (enemy1->tank_enemy.getGlobalBounds().intersects(enemy2->tank_enemy.getGlobalBounds()))
			{
				if (enemy1->tank_enemy.getPosition().x < enemy2->tank_enemy.getPosition().x)
				{
					enemy1->tank_enemy.setPosition(enemy1->tank_enemy.getPosition().x - 2, enemy1->tank_enemy.getPosition().y);
					enemy2->tank_enemy.setPosition(enemy2->tank_enemy.getPosition().x + 2, enemy2->tank_enemy.getPosition().y);
				}
				else if (enemy1->tank_enemy.getPosition().x > enemy2->tank_enemy.getPosition().x)
				{
					enemy1->tank_enemy.setPosition(enemy1->tank_enemy.getPosition().x + 2, enemy1->tank_enemy.getPosition().y);
					enemy2->tank_enemy.setPosition(enemy2->tank_enemy.getPosition().x - 2, enemy2->tank_enemy.getPosition().y);
				}
				else if (enemy1->tank_enemy.getPosition().y < enemy2->tank_enemy.getPosition().y)
				{
					enemy1->tank_enemy.setPosition(enemy1->tank_enemy.getPosition().x, enemy1->tank_enemy.getPosition().y - 2);
					enemy2->tank_enemy.setPosition(enemy2->tank_enemy.getPosition().x, enemy2->tank_enemy.getPosition().y + 2);
				}
				else if (enemy1->tank_enemy.getPosition().y > enemy2->tank_enemy.getPosition().y)
				{
					enemy1->tank_enemy.setPosition(enemy1->tank_enemy.getPosition().x, enemy1->tank_enemy.getPosition().y + 2);
					enemy2->tank_enemy.setPosition(enemy2->tank_enemy.getPosition().x, enemy2->tank_enemy.getPosition().y - 2);
				}
			}
		}
	}
}


void Collision::detectCollision(std::vector<std::unique_ptr<TankEnemy>>& enemies) const
{
	verticalCollision(enemies);
	horizontalCollision(enemies);
	borderCollision(enemies);

	bulletColliion(enemies);
	enemiesSelfCollisions(enemies);
	detectEnemyCollisions(enemies);
}


