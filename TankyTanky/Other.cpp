#include "Other.h"


void Other::createFilesFolder()
{
	auto file_creation_task = std::async(std::launch::async, []()
		{
			if (!std::filesystem::exists("files"))
			{
				std::filesystem::create_directory("files");
			}

			if (!std::filesystem::exists("files/author.txt"))
			{
				std::ofstream author_file("files/author.txt");
				if (author_file.is_open())
				{
					author_file << "Author: Michal Kaminski, gr. 6\n";
					author_file << "Subject: Computer Programming, semester 4 (2024)\n";
					author_file << "Faculty: Politechnika Slaska, AEI, Gliwice\n";
					author_file << "Studies: Informatics [PL] SSI\n";
					author_file << "Name: TankyTanky\n";
				}
				author_file.close();
			}

			if (!std::filesystem::exists("files/players.txt"))
			{
				std::ofstream players_file("files/players.txt");
				std::filesystem::permissions("files/players.txt", std::filesystem::perms::owner_read | std::filesystem::perms::owner_write | std::filesystem::perms::group_read | std::filesystem::perms::others_read);
				players_file.close();
			}

			if (!std::filesystem::exists("files/leaderboard.txt"))
			{
				std::ofstream scores_file("files/leaderboard.txt");
				std::filesystem::permissions("files/leaderboard.txt", std::filesystem::perms::owner_read | std::filesystem::perms::owner_write | std::filesystem::perms::group_read | std::filesystem::perms::others_read);
				scores_file.close();
			}
		});

	file_creation_task.wait();
}


void Other::makingImages(const float& x, const float& y, sf::RenderWindow& window)
{
	sf::Texture texture;
	sf::Sprite sprite;

	if (std::filesystem::exists("files/rudy.jpg"))
	{
		texture.loadFromFile("files/rudy.jpg");
	}
	else
	{
		writingText(425, 525, 19, 2, "Error loading image - contact with the admin", sf::Color::Red, sf::Color::Black, sf::Text::Regular, window);
	}

	auto textureLoadingTask = std::async(std::launch::async, [&]()
		{
			sprite.setTexture(texture);
			sprite.setPosition(sf::Vector2f(x, y));
			texture.setSmooth(true);
		});

	textureLoadingTask.wait();

	window.draw(sprite);
}


sf::Font& Other::getFont()
{
	static sf::Font font;
	static bool is_loaded = false;

	try
	{
		if (!is_loaded)
		{
			if (std::filesystem::exists("files/calibri.ttf"))
			{
				if (!font.loadFromFile("files/calibri.ttf"))
				{
					throw std::runtime_error("Error loading font from file - download calibri.ttf and put it in the files folder");
				}
				is_loaded = true;
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		system("pause");
		exit(1);
	}
	return font;
}


void Other::writingText(const float& x, const float& y, const float& size, const float& thickness, const std::string& world, const sf::Color& primary_color, const sf::Color& thickenss_color, sf::Text::Style style, sf::RenderWindow& window)
{
	sf::Text text;
	text.setFont(getFont());
	text.setPosition(sf::Vector2f(x, y));
	text.setCharacterSize(static_cast<unsigned int>(size));
	text.setFillColor(primary_color);
	text.setString(world);
	text.setStyle(style);
	text.setOutlineThickness(thickness);
	text.setOutlineColor(thickenss_color);

	window.draw(text);
}
