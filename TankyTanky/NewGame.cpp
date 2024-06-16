#include "NewGame.h"


void NewGame::runNewGame(std::vector<std::unique_ptr<Button>>& buttons, sf::RectangleShape& border, TextBox& text_box, const sf::Event& event, sf::RenderWindow& window)
{
	window.clear(sf::Color(154, 217, 234));

	buttons[1]->turnOffButton();
	buttons[2]->turnOffButton();
	buttons[3]->turnOffButton();
	buttons[4]->turnOffButton();

	text_box.clearTextBox();

	buttons[5]->clickButton(event, window);

	std::vector<std::unique_ptr<Tank>> tanks;

	if (tanks.empty())
	{
		tanks.emplace_back(std::make_unique<Tank>(50, 73, 170, sf::Color::Transparent));
		tanks.emplace_back(std::make_unique<Tank>(3, 200, 180, sf::Color::Transparent));
		tanks.emplace_back(std::make_unique<Tank>(4, 73, 300, sf::Color::Transparent));
		tanks.emplace_back(std::make_unique<Tank>(5, 200, 300, sf::Color::Transparent));
		tanks.emplace_back(std::make_unique<Tank>(6, 73, 430, sf::Color::Transparent));
		tanks.emplace_back(std::make_unique<Tank>(8, 200, 430, sf::Color::Transparent));
	}
	
	std::vector<std::unique_ptr<Button>> color_tanks;
	
	if (color_tanks.empty())
	{
		color_tanks.emplace_back(std::make_unique<Button>(10, 600, 75, 75, sf::Color::Blue, sf::Color::Blue));
		color_tanks.emplace_back(std::make_unique<Button>(110, 600, 75, 75, sf::Color::Red, sf::Color::Red));
		color_tanks.emplace_back(std::make_unique<Button>(210, 600, 75, 75, sf::Color::Yellow, sf::Color::Yellow));
		color_tanks.emplace_back(std::make_unique<Button>(310, 600, 75, 75, sf::Color(0, 100, 0), sf::Color(0, 100, 0)));
		color_tanks.emplace_back(std::make_unique<Button>(410, 600, 75, 75, sf::Color::Magenta, sf::Color::Magenta));
		color_tanks.emplace_back(std::make_unique<Button>(510, 600, 75, 75, sf::Color(255, 165, 0), sf::Color(255, 165, 0)));
		color_tanks.emplace_back(std::make_unique<Button>(610, 600, 75, 75, sf::Color::White, sf::Color::White));
		color_tanks.emplace_back(std::make_unique<Button>(710, 600, 75, 75, sf::Color(148, 0, 211), sf::Color(148, 0, 211)));
	}

	for (auto& color_tank : color_tanks)
	{
		color_tank->clickButton(event, window);

		if (color_tank->isClicked())
		{
			color_tank->button_clicked = true;
		}
	}

	for (auto& tank : tanks) 
	{
		tank->clickButton(event, window);

		if (tank->isClicked())
		{
			tank->button_clicked = true;
		}

		if (color_tanks[0]->isClicked())
		{
			tank->changeColor(color_tanks[0]->shape.getFillColor());
			TankPlayer::tank_player.setFillColor(color_tanks[0]->shape.getFillColor());
		}
		else if (color_tanks[1]->isClicked())
		{
			tank->changeColor(color_tanks[1]->shape.getFillColor());
			TankPlayer::tank_player.setFillColor(color_tanks[1]->shape.getFillColor());
		}
		else if (color_tanks[2]->isClicked())
		{
			tank->changeColor(color_tanks[2]->shape.getFillColor());
			TankPlayer::tank_player.setFillColor(color_tanks[2]->shape.getFillColor());
		}
		else if (color_tanks[3]->isClicked())
		{
			tank->changeColor(color_tanks[3]->shape.getFillColor());
			TankPlayer::tank_player.setFillColor(color_tanks[3]->shape.getFillColor());
		}
		else if (color_tanks[4]->isClicked())
		{
			tank->changeColor(color_tanks[4]->shape.getFillColor());
			TankPlayer::tank_player.setFillColor(color_tanks[4]->shape.getFillColor());
		}
		else if (color_tanks[5]->isClicked())
		{
			tank->changeColor(color_tanks[5]->shape.getFillColor());
			TankPlayer::tank_player.setFillColor(color_tanks[5]->shape.getFillColor());
		}
		else if (color_tanks[6]->isClicked())
		{
			tank->changeColor(color_tanks[6]->shape.getFillColor());
			TankPlayer::tank_player.setFillColor(color_tanks[6]->shape.getFillColor());
		}
		else if (color_tanks[7]->isClicked())
		{
			tank->changeColor(color_tanks[7]->shape.getFillColor());
			TankPlayer::tank_player.setFillColor(color_tanks[7]->shape.getFillColor());
		}
	}

	Other::writingText(175, 5, 60, 2, "Create your tank", sf::Color::Black, sf::Color::White, sf::Text::Style::Bold, window);
	Other::writingText(100, 90, 30, 1, "Choose figure", sf::Color(0, 100, 0), sf::Color::White, sf::Text::Style::Bold, window);
	Other::writingText(525, 90, 30, 1, "Enter name", sf::Color(0, 100, 0), sf::Color::White, sf::Text::Style::Bold, window);
	Other::writingText(300, 550, 30, 1, "Choose color", sf::Color(0, 100, 0), sf::Color::White, sf::Text::Style::Bold, window);
	Other::writingText(315, 200, 23, 1, "You must choose a color, a figure and a name!", sf::Color::Red, sf::Color::White, sf::Text::Style::Bold, window);
	Other::writingText(10, 130, 11, 1, "If you can't click Play: check entered name (only letters and numbers) and probably the same name already exists - and click enter after writing", sf::Color::Red, sf::Color::White, sf::Text::Style::Bold, window);

	sf::RectangleShape figure_frame(sf::Vector2f(125.f, 125.f));
	figure_frame.setFillColor(sf::Color::Transparent);
	figure_frame.setOutlineThickness(2);
	figure_frame.setOutlineColor(sf::Color::Black);
	figure_frame.setOrigin(-50, -150);

	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 2; col++)
		{
			figure_frame.setPosition(col * (127.f), row * (127.f));
			window.draw(figure_frame);
		}
	}

	if (buttons[5]->isClicked())
	{
		if (Tank::tank_shape_copy.getFillColor() != sf::Color::Transparent and Tank::figure_check == true and TextBox::text_check == true)
		{
			std::fstream players_file;
			players_file.open("files/players.txt", std::ios::app);
			if (players_file.good())
			{
				players_file << TextBox::input_text << std::endl;
				players_file.close();
			}
			else
			{
				Other::createFilesFolder();
				players_file << TextBox::input_text << std::endl;
				players_file.close();
			}

			TextBox::text_check = false;

			window.close();
			Game game;
			game.runGame();
		}

		buttons[1]->turnOffButton();
		buttons[2]->turnOffButton();
		buttons[3]->turnOffButton();
		buttons[4]->turnOffButton();
		buttons[5]->turnOffButton();

		buttons[5]->button_clicked = true;
	}

	for (auto& tank : tanks)
	{
		window.draw(*tank);
	}

	for (auto& color_tank : color_tanks)
	{
		window.draw(*color_tank);
	}

	window.draw(border);
	window.draw(*buttons[5]);
	window.draw(text_box);

	Other::writingText(565, 450, 40, 2, "Play", sf::Color::Black, sf::Color::White, sf::Text::Style::Bold, window);
}
