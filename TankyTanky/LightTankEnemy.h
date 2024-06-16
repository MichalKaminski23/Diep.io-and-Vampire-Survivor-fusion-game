#pragma once


#include "TankEnemy.h"


class LightTankEnemy : public TankEnemy
{
public:

	LightTankEnemy(const int& point_count, const float& x, const float& y, const sf::Color& color);

	~LightTankEnemy() = default;

	virtual sf::Vector2f calculateEnemiesVelocity() override;

	virtual void shoot(sf::RenderWindow& window) override;
};

