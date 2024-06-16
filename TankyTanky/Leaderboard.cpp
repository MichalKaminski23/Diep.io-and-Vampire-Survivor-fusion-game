#include "Leaderboard.h"


int Leaderboard::leaderboard_guard = 0;


void Leaderboard::createPage(Page& page, const std::vector<std::pair<int, PlayerInfo>>& data, float start_index, float results_per_page, sf::RenderWindow& window)
{
	page.texts.clear();
	page.tanks.clear();

	sf::CircleShape leaderboard_tank;
	leaderboard_tank.setRadius(20);
	leaderboard_tank.setOutlineColor(sf::Color::Black);
	leaderboard_tank.setOutlineThickness(2);

	for (float i = start_index; i < start_index + results_per_page && i < data.size(); ++i)
	{
		std::string text = "POINTS: " + std::to_string(data[i].first) + "  " +
			"NAME: " + data[i].second.name + "  " +
			"DATE: " + data[i].second.date + "  ";

		TextInfo textInfo;
		textInfo.x = 15;
		textInfo.y = 200 + (i - start_index) * 100;
		textInfo.character_size = 26;
		textInfo.outline_thickness = 0;
		textInfo.text = text;
		textInfo.fill_color = sf::Color::Black;
		textInfo.outline_color = sf::Color::White;
		textInfo.style = sf::Text::Regular;

		page.texts.push_back(textInfo);

		switch (data[i].second.color_number)
		{
		case 1:
			leaderboard_tank.setFillColor(sf::Color::Blue);
			break;
		case 2:
			leaderboard_tank.setFillColor(sf::Color::Red);
			break;
		case 3:
			leaderboard_tank.setFillColor(sf::Color::Yellow);
			break;
		case 4:
			leaderboard_tank.setFillColor(sf::Color(0, 100, 0));
			break;
		case 5:
			leaderboard_tank.setFillColor(sf::Color::Magenta);
			break;
		case 6:
			leaderboard_tank.setFillColor(sf::Color(255, 165, 0));
			break;
		case 7:
			leaderboard_tank.setFillColor(sf::Color::White);
			break;
		case 8:
			leaderboard_tank.setFillColor(sf::Color(148, 0, 211));
			break;
		}

		leaderboard_tank.setPointCount(data[i].second.figure_number);
		leaderboard_tank.setPosition(650, 200 + (i - start_index) * 100);

		page.tanks.push_back(leaderboard_tank);
	}
}


void Leaderboard::runLeaderboard(std::vector<std::unique_ptr<Button>>& buttons, sf::RectangleShape& border, const sf::Event& event, sf::RenderWindow& window)
{
	window.clear(sf::Color(154, 217, 234));

	std::vector<std::pair<int, PlayerInfo>> data = Game::readFromFile();

	buttons[0]->turnOffButton();
	buttons[2]->turnOffButton();
	buttons[3]->turnOffButton();
	buttons[5]->turnOffButton();

	buttons[4]->clickButton(event, window);

	std::vector<std::unique_ptr<Button>> page_buttons;

	if (page_buttons.empty())
	{
		page_buttons.emplace_back(std::make_unique<NextButton>(550, 700, 200, 50, sf::Color(255, 165, 0), sf::Color::Yellow)); // NEXT 0
		page_buttons.emplace_back(std::make_unique<BackButton>(50, 700, 200, 50, sf::Color(0, 100, 0), sf::Color::Magenta)); // BACK 1
	}

	page_buttons[0]->clickButton(event, window);
	page_buttons[1]->clickButton(event, window);

	const unsigned int results_per_page = 5;

	Button::pages.clear();

	for (unsigned int i = 0; i < data.size(); i += results_per_page)
	{
		Page page = { {} };
		createPage(page, data, i, results_per_page, window);
		Button::pages.push_back(page);
	}

	if (Button::current_page_index >= Button::pages.size())
	{
		Button::current_page_index = Button::pages.size() - 1;
	}

	if (Button::current_page_index >= 0 && Button::current_page_index < Button::pages.size())
	{
		for (const auto& textInfo : Button::pages[Button::current_page_index].texts)
		{
			Other::writingText(textInfo.x, textInfo.y, textInfo.character_size, textInfo.outline_thickness, textInfo.text, textInfo.fill_color, textInfo.outline_color, textInfo.style, window);
		}

		for (const auto& tank : Button::pages[Button::current_page_index].tanks)
		{
			window.draw(tank);
		}
	}

	window.draw(*buttons[4]);
	window.draw(*page_buttons[0]);
	window.draw(*page_buttons[1]);
	window.draw(border);

	Other::writingText(225, 100, 60, 2, "HALL OF FAME", sf::Color::Black, sf::Color::Red, sf::Text::Style::Italic, window);
	Other::writingText(135, 35, 40, 2, "Back", sf::Color::Black, sf::Color::White, sf::Text::Style::Bold, window);
	Other::writingText(625, 715, 20, 2, "NEXT", sf::Color::Black, sf::Color::White, sf::Text::Style::Bold, window);
	Other::writingText(125, 715, 20, 2, "BACK", sf::Color::Black, sf::Color::White, sf::Text::Style::Bold, window);
}

