#pragma once


#include "Button.h"


class Author
{
public:

	Author() = default;

	~Author() = default;

	void runAuthor(std::vector<std::unique_ptr<Button>>& buttons, sf::RectangleShape& border, const sf::Event& event, sf::RenderWindow& window);

	static int author_guard;

};


