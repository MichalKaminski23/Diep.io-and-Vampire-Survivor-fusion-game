#include "Author.h"


int Author::author_guard = 0;


void Author::runAuthor(std::vector<std::unique_ptr<Button>>& buttons, sf::RectangleShape& border, const sf::Event& event, sf::RenderWindow& window)
{
	window.clear(sf::Color(154, 217, 234));

	buttons[0]->turnOffButton();
	buttons[1]->turnOffButton();
	buttons[3]->turnOffButton();
	buttons[5]->turnOffButton();

	buttons[4]->clickButton(event, window);

	std::fstream author_file;
	author_file.open("files/author.txt", std::ios::in);

	if (!author_file)
	{
		Other::writingText(275, 350, 35, 2, "Author file not found", sf::Color::Red, sf::Color::Black, sf::Text::Regular, window);
	}

	std::string text;
	std::string line;

	while (getline(author_file, line))
	{
		text += line + "\n";
	}

	author_file.close();

	window.draw(*buttons[4]);
	window.draw(border);

	Other::writingText(10, 350, 35, 2, text, sf::Color::White, sf::Color::Black, sf::Text::Style::Bold, window);
	Other::writingText(135, 35, 40, 2, "Back", sf::Color::Black, sf::Color::White, sf::Text::Style::Bold, window);
}