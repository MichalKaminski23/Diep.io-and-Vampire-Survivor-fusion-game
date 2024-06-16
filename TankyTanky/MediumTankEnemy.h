#pragma once


#include "TankEnemy.h"


class MediumTankEnemy : public TankEnemy
{
public:

	MediumTankEnemy(const int& point_count, const float& x, const float& y, const sf::Color& color);

	~MediumTankEnemy() = default;

	virtual sf::Vector2f calculateEnemiesVelocity() override;

	virtual void shoot(sf::RenderWindow& window) override;
};

