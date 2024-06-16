#pragma once


#include "TankEnemy.h"


class HeavyTankEnemy : public TankEnemy
{
public:

	HeavyTankEnemy(const int& point_count, const float& x, const float& y, const sf::Color& color);

	~HeavyTankEnemy() = default;

	virtual sf::Vector2f calculateEnemiesVelocity() override;

	virtual void shoot(sf::RenderWindow& window) override;
};

