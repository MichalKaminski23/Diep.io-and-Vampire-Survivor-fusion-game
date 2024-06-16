#pragma once


#include "Drawing.h"
#include "Tank.h"


class TankEnemy : public Drawing
{
public:

	virtual ~TankEnemy() = default;

	virtual void kill();

	static void shootPlayer(std::vector<std::unique_ptr<TankEnemy>>& enemies, sf::RenderWindow& window);

	static void moveEnemies(std::vector<std::unique_ptr<TankEnemy>>& enemies, const float& dt);

	sf::Vector2f getEnemyPosition() const;

	sf::Vector2f getPlayerPosition() const;

	static int enemies_left;

	static int enemies_killed;

	static int sum_enemies_bullets;

	static int wave_count;

	float enemy_health;

	float enemy_bullet_damage;

	float enemy_body_damage;

	std::vector<float> enemy_angles;

	std::vector<std::unique_ptr<sf::CircleShape>> enemy_bullets;

	sf::CircleShape tank_enemy;

	sf::Clock clock;

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual void shoot(sf::RenderWindow& window) = 0;

	virtual bool isAlive() const;

	virtual sf::Vector2f calculateEnemiesVelocity() = 0;

	bool alive = true;
};
