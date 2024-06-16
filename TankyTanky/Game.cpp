#include "Game.h"


sf::Clock Game::game_clock;
std::string Game::final_game_time;


Game::Game()
{
	window.emplace_back(std::make_unique<sf::RenderWindow>(sf::VideoMode(1200, 1000), "TankyTanky", sf::Style::Titlebar | sf::Style::Close));
	window[0]->setPosition((sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - 650, sf::VideoMode::getDesktopMode().height / 2 - 540)));
}


std::string Game::countTime()
{
	sf::Time elapsed = game_clock.getElapsedTime();

	int game_time_seconds = static_cast<int>(elapsed.asSeconds());
	int hours = game_time_seconds / 3600;
	int minutes = (game_time_seconds % 3600) / 60;
	int seconds = game_time_seconds % 60;

	std::stringstream time_stream;
	time_stream << hours << ":" << (minutes < 10 ? "0" : "") << minutes << ":" << (seconds < 10 ? "0" : "") << seconds;
	std::string game_time_str = time_stream.str();

	if (TankPlayer::player_health <= 0)
	{
		final_game_time = game_time_str;
		is_game_over = true;
	}

	if (is_game_over)
	{
		return final_game_time;
	}

	return game_time_str;
}


std::string Game::getCurrentDate()
{
	std::time_t now = std::time(0);
	std::tm localtime;

	localtime_s(&localtime, &now);
	char buffer[80];

	std::strftime(buffer, sizeof(buffer), "%d-%m-%Y", &localtime);

	return std::string(buffer);
}


void Game::writeStatistics(sf::RenderWindow& window)
{
	std::string current_time = countTime();

	sf::RectangleShape stats_frame;
	stats_frame.setSize(sf::Vector2f(250, 125));
	stats_frame.setFillColor(sf::Color(200, 200, 200, 100));
	stats_frame.setOutlineThickness(3);
	stats_frame.setOutlineColor(sf::Color(255, 165, 0, 150));
	stats_frame.setPosition(500, 5);

	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << TankPlayer::player_health;
	std::string player_health_str = stream.str();

	Other::writingText(stats_frame.getPosition().x, stats_frame.getPosition().y, 24, 1, "Player's health: ", sf::Color::Black, sf::Color::White, sf::Text::Style::Bold, window);
	Other::writingText(stats_frame.getPosition().x + 180, stats_frame.getPosition().y, 24, 1, player_health_str, sf::Color::Red, sf::Color::White, sf::Text::Style::Bold, window);

	Other::writingText(stats_frame.getPosition().x, stats_frame.getPosition().y + 30, 24, 1, "Enemies left: ", sf::Color::Black, sf::Color::White, sf::Text::Style::Bold, window);
	Other::writingText(stats_frame.getPosition().x + 180, stats_frame.getPosition().y + 30, 24, 1, std::to_string(TankEnemy::enemies_left), sf::Color::Magenta, sf::Color::White, sf::Text::Style::Bold, window);

	Other::writingText(stats_frame.getPosition().x, stats_frame.getPosition().y + 60, 24, 1, "Wave number: ", sf::Color::Black, sf::Color::White, sf::Text::Style::Bold, window);
	Other::writingText(stats_frame.getPosition().x + 180, stats_frame.getPosition().y + 60, 24, 1, std::to_string(TankEnemy::wave_count), sf::Color(0, 100, 0), sf::Color::White, sf::Text::Style::Bold, window);

	Other::writingText(stats_frame.getPosition().x, stats_frame.getPosition().y + 90, 24, 1, "Game time: ", sf::Color::Black, sf::Color::White, sf::Text::Style::Bold, window);
	Other::writingText(stats_frame.getPosition().x + 140, stats_frame.getPosition().y + 90, 24, 1, current_time, sf::Color::Blue, sf::Color::White, sf::Text::Style::Bold, window);

	window.draw(stats_frame);
}


std::vector<std::pair<int, PlayerInfo>> Game::readFromFile()
{
	std::vector<std::pair<int, PlayerInfo>> data;

	std::ifstream in_file("files/leaderboard.txt");
	std::string line;

	while (std::getline(in_file, line))
	{
		if (line.find("Points: ") == 0)
		{
			int points = std::stoi(line.substr(8));
			PlayerInfo info;

			std::getline(in_file, line);
			info.name = line.substr(13);

			std::getline(in_file, line);
			info.date = line.substr(11);

			std::getline(in_file, line);
			info.color_number = std::stoi(line.substr(12));

			std::getline(in_file, line);
			info.figure_number = std::stoi(line.substr(11));

			data.emplace_back(points, info);

			std::getline(in_file, line);
		}
	}

	in_file.close();
	return data;
}


void Game::writeToFile(const std::vector<std::pair<int, PlayerInfo>>& data)
{
	std::ofstream out_file("files/leaderboard.txt");

	for (const auto& entry : data)
	{
		out_file << "Points: " << entry.first << std::endl;
		out_file << "Player Name: " << entry.second.name << std::endl;
		out_file << "Game Date: " << entry.second.date << std::endl;
		out_file << "Tank color: " << entry.second.color_number << std::endl;
		out_file << "Tank type: " << entry.second.figure_number << std::endl;
		out_file << "---------------------------" << std::endl;
	}

	out_file.close();
}


void Game::endGame()
{
	window[0]->setMouseCursorVisible(true);

	std::string current_date = getCurrentDate();

	std::unordered_map<int, PlayerInfo> leaderboard_umap;
	leaderboard_umap[TankEnemy::wave_count] = { TextBox::input_text, current_date, TankPlayer::getTankPlayerColor(), TankPlayer::getTankPlayerFigure() };

	std::vector<std::pair<int, PlayerInfo>> leaderobard_vector(leaderboard_umap.begin(), leaderboard_umap.end());
	std::ranges::sort(leaderobard_vector, std::greater{}, &std::pair<int, PlayerInfo>::first);

	std::vector<std::pair<int, PlayerInfo>> leaderboard_file = readFromFile();
	leaderboard_file.insert(leaderboard_file.end(), leaderobard_vector.begin(), leaderobard_vector.end());
	std::ranges::sort(leaderboard_file, std::greater{}, &std::pair<int, PlayerInfo>::first);

	writeToFile(leaderboard_file);

	std::vector<std::unique_ptr<Button>> end_game_buttons;

	if (end_game_buttons.empty())
	{
		end_game_buttons.emplace_back(std::make_unique<Button>(450, 700, 350, 125, sf::Color(255, 165, 0), sf::Color::Yellow)); //menu
		end_game_buttons.emplace_back(std::make_unique<Button>(450, 830, 350, 125, sf::Color(255, 192, 203), sf::Color(148, 0, 211))); //exit
	}

	while (window[0]->isOpen())
	{
		window[0]->clear(sf::Color(200, 200, 200));

		Other::writingText(425, 100, 80, 2, "GAME OVER", sf::Color::Red, sf::Color::White, sf::Text::Style::Bold, *window[0]);

		Other::writingText(350, 200, 40, 1, "Waves defeated: ", sf::Color::Black, sf::Color::White, sf::Text::Style::Bold, *window[0]);
		Other::writingText(775, 200, 40, 1, std::to_string(TankEnemy::wave_count), sf::Color(0, 100, 0), sf::Color::White, sf::Text::Style::Bold, *window[0]);

		Other::writingText(350, 250, 40, 1, "Enemies killed: ", sf::Color::Black, sf::Color::White, sf::Text::Style::Bold, *window[0]);
		Other::writingText(775, 250, 40, 1, std::to_string(TankEnemy::enemies_killed), sf::Color::Magenta, sf::Color::White, sf::Text::Style::Bold, *window[0]);

		Other::writingText(350, 300, 40, 1, "Bullets fired (player): ", sf::Color::Black, sf::Color::White, sf::Text::Style::Bold, *window[0]);
		Other::writingText(775, 300, 40, 1, std::to_string(TankPlayer::sum_player_bullets), sf::Color(75, 0, 130), sf::Color::White, sf::Text::Style::Bold, *window[0]);

		Other::writingText(350, 350, 40, 1, "Bullets fired (enemies): ", sf::Color::Black, sf::Color::White, sf::Text::Style::Bold, *window[0]);
		Other::writingText(775, 350, 40, 1, std::to_string(TankEnemy::sum_enemies_bullets), sf::Color::Green, sf::Color::White, sf::Text::Style::Bold, *window[0]);

		Other::writingText(350, 400, 40, 1, "Time spent: ", sf::Color::Black, sf::Color::White, sf::Text::Style::Bold, *window[0]);
		Other::writingText(775, 400, 40, 1, final_game_time, sf::Color::Blue, sf::Color::White, sf::Text::Style::Bold, *window[0]);

		Other::writingText(350, 450, 40, 1, "Today's date: ", sf::Color::Black, sf::Color::White, sf::Text::Style::Bold, *window[0]);
		Other::writingText(775, 450, 40, 1, current_date, sf::Color::Blue, sf::Color::White, sf::Text::Style::Bold, *window[0]);

		Other::writingText(50, 500, 40, 1, "Thank you ", sf::Color(255, 128, 0), sf::Color::White, sf::Text::Style::Bold, *window[0]);
		Other::writingText(350, 500, 40, 2, TextBox::input_text, sf::Color(153, 0, 76), sf::Color::White, sf::Text::Style::Bold, *window[0]);
		Other::writingText(950, 500, 40, 1, "for playing!", sf::Color(255, 128, 0), sf::Color::White, sf::Text::Style::Bold, *window[0]);

		TankPlayer::tank_player.setPosition(sf::Vector2f(625, 600));
		TankPlayer::tank_player.setScale(1.5, 1.5);
		TankPlayer::tank_player.setRotation(0);
		window[0]->draw(TankPlayer::tank_player);

		sf::Event event;
		while (window[0]->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window[0]->close();
			}

			for (int i = 0; i < 2; ++i)
			{
				end_game_buttons[i]->clickButton(event, *window[0]);
			}
		}

		for (int i = 0; i < 2; ++i)
		{
			window[0]->draw(*end_game_buttons[i]);
		}

		Other::writingText(500, 735, 40, 2, "Back to menu :)", sf::Color::Black, sf::Color::White, sf::Text::Style::Bold, *window[0]);
		Other::writingText(585, 865, 40, 2, "Exit :(", sf::Color::Black, sf::Color::White, sf::Text::Style::Bold, *window[0]);

		if (end_game_buttons[0]->isClicked())
		{
			window[0]->close();
			Menu menu;
			menu.runMenu();
		}

		if (end_game_buttons[1]->isClicked())
		{
			window[0]->close();
		}

		window[0]->display();
	}
}


void Game::spawnEnemies(std::vector<std::unique_ptr<TankEnemy>>& enemies, sf::RenderWindow& window)
{
	srand(static_cast<unsigned int>(time(nullptr)));

	if (enemies.empty())
	{
		TankPlayer::player_bullets.clear();
		TankPlayer::player_angles.clear();

		TankEnemy::wave_count++;

		if (TankEnemy::wave_count % 2 == 0)
		{
			TankPlayer::pause = true;
		}

		TankEnemy::enemies_left = TankEnemy::wave_count;

		for (int i = 0; i < TankEnemy::wave_count; i++)
		{
			float rand_x = static_cast<float>(rand() % (window.getSize().x - 60));
			float rand_y = static_cast<float>(rand() % (window.getSize().y - 60));

			sf::Color rand_color = sf::Color(rand() % 256, rand() % 256, rand() % 256);

			float rand_point_count;

			int shape_type = rand() % 2;

			if (shape_type == 0)
			{
				rand_point_count = static_cast<float>(rand() % 8 + 3);
			}
			else
			{
				rand_point_count = 50;
			}

			if (i % 2 == 0)
			{
				enemies.emplace_back(std::make_unique<MediumTankEnemy>(rand_point_count, rand_x, rand_y, rand_color));
			}
			else if (i % 3 == 0)
			{
				enemies.emplace_back(std::make_unique<HeavyTankEnemy>(rand_point_count, rand_x, rand_y, rand_color));
			}
			else
			{
				enemies.emplace_back(std::make_unique<LightTankEnemy>(rand_point_count, rand_x, rand_y, rand_color));
			}
		}
	}

	for (const auto& enemy : enemies)
	{
		window.draw(*enemy);
	}
}


void Game::runGame()
{
	Game::game_clock.restart();

	std::vector<std::unique_ptr<TankEnemy>> enemies;

	TankPlayer::player_health = 10;
	TankPlayer::player_max_health = TankPlayer::player_health;
	TankPlayer::player_speed = 200.0f;
	TankPlayer::player_body_damage = 1.0f;
	TankPlayer::player_bullet_damage = 1.0f;
	TankPlayer::player_bullet_delay = 1.f;
	TankPlayer::player_bullet_speed = 5.0f;

	TankPlayer::sum_player_bullets = 0;
	TankEnemy::enemies_left = 0;
	TankEnemy::wave_count = 0;
	TankEnemy::enemies_killed = 0;
	TankEnemy::sum_enemies_bullets = 0;

	Collision border(1196, 996); //FRAME
	Collision L1(110, 100, 100, Collision::Direction::LT); //LEFT TOP
	Collision L2(1075, 100, 100, Collision::Direction::LB); //LEFT BOTTOM
	Collision L3(110, 680, 100, Collision::Direction::RT); //RIGHT TOP
	Collision L4(1075, 680, 100, Collision::Direction::RB); //RITHT BOTTOM

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

	sf::Clock clock;

	while (window[0]->isOpen())
	{
		window[0]->clear(sf::Color(200, 200, 200));
		window[0]->setMouseCursorVisible(false);

		sf::Time delta_time = clock.restart();
		float dt = delta_time.asSeconds();

		sf::Event event;
		while (window[0]->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window[0]->close();
			}
		}

		window[0]->draw(border);
		window[0]->draw(L1);
		window[0]->draw(L2);
		window[0]->draw(L3);
		window[0]->draw(L4);
		window[0]->draw(TankPlayer::tank_player);

		if (TankPlayer::pause == false)
		{
			clock.restart();

			spawnEnemies(enemies, *window[0]);

			TankEnemy::moveEnemies(enemies, dt);
			TankEnemy::shootPlayer(enemies, *window[0]);

			TankPlayer::moveTank(clock, delta_time, dt, *window[0]);
			TankPlayer::shootBullet(*window[0]);

			border.detectCollision(enemies);
			L1.detectCollision(enemies);
			L2.detectCollision(enemies);
			L3.detectCollision(enemies);
			L4.detectCollision(enemies);

			writeStatistics(*window[0]);
		}

		if (TankPlayer::pause == true)
		{
			TankPlayer::playerUpgrade(*window[0], event);
			clock.restart();
			TankPlayer::upgrade_selected = false;
			TankPlayer::player_health = TankPlayer::player_max_health;
		}

		if (TankPlayer::player_health <= 0)
		{
			endGame();
		}

		window[0]->display();
	}
}