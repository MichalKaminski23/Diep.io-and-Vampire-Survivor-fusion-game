#pragma once


#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>


struct PlayerInfo
{
	std::string name;
	std::string date;
	int color_number;
	int figure_number;
};


struct TextInfo
{
    float x;
    float y;
    int character_size;
    int outline_thickness;
    std::string text;
    sf::Color fill_color;
    sf::Color outline_color;
    sf::Text::Style style;
};


struct Page
{
    std::vector<TextInfo> texts;
    std::vector<sf::CircleShape> tanks;
};
