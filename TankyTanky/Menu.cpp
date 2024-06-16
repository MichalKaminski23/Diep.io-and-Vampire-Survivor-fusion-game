#include "Menu.h"


Menu::Menu()
{
	window.emplace_back(std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 800), "TankyTanky", sf::Style::Titlebar | sf::Style::Close));
	window[0]->setPosition((sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - 450, sf::VideoMode::getDesktopMode().height / 2 - 475)));
}


void Menu::runMenu()
{
	Other::createFilesFolder();

	window[0]->setMouseCursorVisible(true);

	sf::Text menu_text;

	sf::Image icon;
	icon.create(32, 32);

	sf::Color rainbow[] =
	{
		sf::Color(255, 0, 0),
		sf::Color(255, 165, 0),
		sf::Color(255, 255, 0),
		sf::Color(0, 128, 0),
		sf::Color(0, 0, 255),
		sf::Color(75, 0, 130),
		sf::Color(148, 0, 211)
	};

	for (int i = 0; i < 7; ++i)
	{
		for (int x = i * 4; x < (i + 1) * 4; ++x)
		{
			for (int y = 0; y < 32; ++y)
			{
				icon.setPixel(x, y, rainbow[i]);
			}
		}
	}

	window[0]->setFramerateLimit(60);
	window[0]->setIcon(32, 32, icon.getPixelsPtr());

	sf::Event event;

	sf::RectangleShape border(sf::Vector2f(796, 796));
	border.setFillColor(sf::Color::Transparent);
	border.setOutlineThickness(2);
	border.setOutlineColor(sf::Color::Black);
	border.setPosition(2, 2);

	std::vector<std::unique_ptr<TextBox>> text_boxes;
	if (text_boxes.empty())
	{
		text_boxes.emplace_back(std::make_unique<TextBox>(sf::Vector2f(450, 150), sf::Vector2f(300, 40)));
	}

	Tank::tank_shape_copy.setFillColor(sf::Color::Transparent);

	//new_game, leaderboard, author, exit, back, play
	//      0,      1,          2,    3,    4,    5     
	std::vector<std::unique_ptr<Button>> buttons;

	if (buttons.empty())
	{
		buttons.emplace_back(std::make_unique<Button>(10, 300, 350, 125, sf::Color(255, 165, 0), sf::Color::Yellow)); //0
		buttons.emplace_back(std::make_unique<Button>(10, 425, 350, 125, sf::Color(0, 100, 0), sf::Color::Magenta)); //1
		buttons.emplace_back(std::make_unique<Button>(10, 550, 350, 125, sf::Color::Blue, sf::Color(75, 0, 130))); //2
		buttons.emplace_back(std::make_unique<Button>(10, 675, 350, 120, sf::Color(255, 192, 203), sf::Color(148, 0, 211))); //3
		buttons.emplace_back(std::make_unique<Button>(10, 10, 350, 100, sf::Color::Green, sf::Color::Red)); //4
		buttons.emplace_back(std::make_unique<Button>(475, 430, 250, 100, sf::Color(255, 165, 0), sf::Color::Yellow)); //5
	}

	while (window[0]->isOpen())
	{
		window[0]->clear(sf::Color(154, 217, 234));

		while (window[0]->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window[0]->close();
			}

			for (int i = 0; i < 4; ++i)
			{
				buttons[i]->clickButton(event, *window[0]);
			}
			text_boxes[0]->clickButton(event, *window[0]);
		}

		for (int i = 0; i < 4; ++i)
		{
			window[0]->draw(*buttons[i]);
		}

		Other::writingText(100, 125, 60, 2, "Welcome to TankyTanky", sf::Color::Black, sf::Color::White, sf::Text::Style::Bold, *window[0]);
		Other::makingImages(375, 350, *window[0]);

		Other::writingText(90, 330, 40, 2, "New Game", sf::Color::Black, sf::Color::White, sf::Text::Style::Bold, *window[0]);
		Other::writingText(75, 455, 40, 2, "Leaderboard", sf::Color::Black, sf::Color::White, sf::Text::Style::Bold, *window[0]);
		Other::writingText(125, 580, 40, 2, "Author", sf::Color::Black, sf::Color::White, sf::Text::Style::Bold, *window[0]);
		Other::writingText(150, 705, 40, 2, "Exit", sf::Color::Black, sf::Color::White, sf::Text::Style::Bold, *window[0]);

		if (Leaderboard::leaderboard_guard == 0)
		{
			if (Author::author_guard == 0)
			{
				if (buttons[0]->isClicked())
				{
					NewGame new_game_fun;
					new_game_fun.runNewGame(buttons, border, *text_boxes[0], event, *window[0]);
				}
			}

			if (buttons[2]->isClicked())
			{
				Author::author_guard = 1;
				Author author_fun;
				author_fun.runAuthor(buttons, border, event, *window[0]);
			}
			if (buttons[3]->isClicked())
			{
				window[0]->close();
			}
		}

		if (buttons[1]->isClicked())
		{
			Leaderboard::leaderboard_guard = 1;
			Leaderboard leaderboard_fun;
			leaderboard_fun.runLeaderboard(buttons, border, event, *window[0]);
		}

		if (buttons[4]->isClicked())
		{
			Leaderboard::leaderboard_guard = 0;
			Author::author_guard = 0;
			runMenu();
		}

		window[0]->draw(border);

		window[0]->display();
	}
}
