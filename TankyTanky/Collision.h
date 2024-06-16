#pragma once


#include "Drawing.h"
#include "TankPlayer.h"


class Collision : public Drawing
{
public:

	enum class Direction { LT, LB, RT, RB };

	Collision(const float& x, const float& y);

	Collision(const float& x, const float& y, const float& size, Direction direction);

	~Collision() = default;

	void detectCollision(std::vector<std::unique_ptr<TankEnemy>>& enemies) const;

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void verticalCollision(std::vector<std::unique_ptr<TankEnemy>>& enemies) const;

	void horizontalCollision(std::vector<std::unique_ptr<TankEnemy>>& enemies) const;

	void borderCollision(std::vector<std::unique_ptr<TankEnemy>>& enemies) const;

	void bulletColliion(std::vector<std::unique_ptr<TankEnemy>>& enemies) const;

	void detectEnemyCollisions(std::vector<std::unique_ptr<TankEnemy>>& enemies) const;

	void enemiesSelfCollisions(std::vector<std::unique_ptr<TankEnemy>>& enemies) const;

	sf::RectangleShape border;

	sf::RectangleShape vertical;

	sf::RectangleShape horizontal;
};

