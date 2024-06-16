#pragma once


#include <ctime>
#include <filesystem>
#include <fstream>
#include <future>
#include <iomanip> 
#include <iostream>
#include <ranges>
#include <regex>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>


class Other
{
public:

	Other() = default;

	~Other() = default;

	static void writingText(const float& x, const float& y, const float& size, const float& thickness, const std::string& world, const sf::Color& primary_color, const sf::Color& thickenss_color, sf::Text::Style style, sf::RenderWindow& window);

	static void makingImages(const float& x, const float& y, sf::RenderWindow& windows);

	static void createFilesFolder();

private:

	static sf::Font& getFont();
};

