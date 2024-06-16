#include "Tank.h"


sf::CircleShape Button::tank_shape_copy;
sf::CircleShape TankPlayer::tank_player;
bool Tank::figure_check = false;


void Tank::onClick(const sf::Event& event, sf::RenderWindow& window)
{
	tank_shape_copy = this->tank_shape;

	this->tank_shape_copy.setRadius(80);
	this->tank_shape_copy.setPosition(sf::Vector2f(525, 250));

	figure_check = true;

	TankPlayer::tank_player = this->tank_shape_copy;
	TankPlayer::tank_player.setRadius(30);
	TankPlayer::tank_player.setOutlineColor(sf::Color::Black);
	TankPlayer::tank_player.setOutlineThickness(3);
	TankPlayer::tank_player.setOrigin(30, 30);
	TankPlayer::tank_player.setPosition(575, 475);
}


void Tank::changeColor(const sf::Color& color)
{
	this->tank_shape_copy.setFillColor(color);
}


sf::Color Tank::getTankColor()
{
	return tank_shape.getFillColor();
}


void Tank::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->tank_shape);
	target.draw(this->tank_shape_copy);
}
