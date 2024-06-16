#pragma once


#include <SFML/Graphics.hpp>


class ClickableObject
{
public:

	virtual ~ClickableObject() = default;

	virtual void onClick(const sf::Event& event, sf::RenderWindow& window) = 0;

};

