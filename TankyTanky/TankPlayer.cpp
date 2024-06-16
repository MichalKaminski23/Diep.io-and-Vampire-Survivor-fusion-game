#include "TankPlayer.h"


#define M_PI 3.14159265358979323846
std::vector<std::unique_ptr<sf::CircleShape>> TankPlayer::player_bullets;
std::vector<float> TankPlayer::player_angles;
float TankPlayer::player_health = 10.f;
float TankPlayer::player_max_health = 10.0f;
float TankPlayer::player_speed = 200.0f;
float TankPlayer::player_body_damage = 1.0f;
float TankPlayer::player_bullet_damage = 1.0f;
float TankPlayer::player_bullet_delay = 1.f;
float TankPlayer::player_bullet_speed = 5.0f;
int TankPlayer::sum_player_bullets = 0;
bool TankPlayer::pause = false;
bool TankPlayer::upgrade_selected = false;
int TankPlayer::color_number = 0;
int TankPlayer::figure_number = 0;


void TankPlayer::moveTank(sf::Clock clock, sf::Time delta_time, float dt, sf::RenderWindow& window)
{
	Other::writingText(TankPlayer::tank_player.getPosition().x - 20, TankPlayer::tank_player.getPosition().y - 15, 20, 1, "YOU", sf::Color(13, 254, 187), sf::Color::Black, sf::Text::Regular, window);

	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movement.x -= 1.0f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movement.x += 1.0f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		movement.y -= 1.0f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		movement.y += 1.0f;
	}

	if (movement.x != 0.0f || movement.y != 0.0f)
	{
		float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
		movement /= length;
	}

	TankPlayer::tank_player.move(movement * TankPlayer::player_speed * dt);

	sf::Vector2i mousePosition = sf::Mouse::getPosition();

	sf::Vector2f direction = static_cast<sf::Vector2f>(mousePosition) - TankPlayer::tank_player.getPosition();

	float rotation = std::atan2(direction.y, direction.x) * 180.f / static_cast<float>(M_PI);

	TankPlayer::tank_player.setRotation(rotation);
}


void TankPlayer::shootBullet(sf::RenderWindow& window)
{
	static sf::Clock clock;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and clock.getElapsedTime().asSeconds() > TankPlayer::player_bullet_delay)
	{
		player_bullets.push_back(std::make_unique<sf::CircleShape>());

		player_bullets.back()->setRadius(5);
		player_bullets.back()->setPosition(sf::Vector2f(TankPlayer::tank_player.getPosition().x - 7, TankPlayer::tank_player.getPosition().y - 5));
		player_bullets.back()->setFillColor(sf::Color::Green);
		player_bullets.back()->setOutlineColor(sf::Color::Black);
		player_bullets.back()->setOutlineThickness(2);
		player_angles.push_back(atan2(sf::Mouse::getPosition(window).y - TankPlayer::tank_player.getPosition().y,
			sf::Mouse::getPosition(window).x - TankPlayer::tank_player.getPosition().x));

		TankPlayer::sum_player_bullets++;

		clock.restart();
	}

	sf::CircleShape scope(10.f);
	scope.setFillColor(sf::Color::Red);
	scope.setOutlineColor(sf::Color::Black);
	scope.setOutlineThickness(1.f);

	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	sf::Vector2f direction = static_cast<sf::Vector2f>(mousePosition) - TankPlayer::tank_player.getPosition();

	float rotation = std::atan2(direction.y, direction.x) * 180.f / static_cast<float>(M_PI);

	scope.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

	scope.setRotation(rotation);

	window.draw(scope);

	for (int i = 0; i < player_bullets.size(); i++)
	{
		player_bullets[i]->move(TankPlayer::player_bullet_speed * cos(player_angles[i]), TankPlayer::player_bullet_speed * sin((player_angles[i])));
		window.draw(*player_bullets[i]);
	}
}


int TankPlayer::getTankPlayerColor()
{
	if (TankPlayer::tank_player.getFillColor() == sf::Color::Blue)
	{
		color_number = 1;
	}
	else if (TankPlayer::tank_player.getFillColor() == sf::Color::Red)
	{
		color_number = 2;
	}
	else if (TankPlayer::tank_player.getFillColor() == sf::Color::Yellow)
	{
		color_number = 3;
	}
	else if (TankPlayer::tank_player.getFillColor() == sf::Color(0, 100, 0))
	{
		color_number = 4;
	}
	else if (TankPlayer::tank_player.getFillColor() == sf::Color::Magenta)
	{
		color_number = 5;
	}
	else if (TankPlayer::tank_player.getFillColor() == sf::Color(255, 165, 0))
	{
		color_number = 6;
	}
	else if (TankPlayer::tank_player.getFillColor() == sf::Color::White)
	{
		color_number = 7;
	}
	else if (TankPlayer::tank_player.getFillColor() == sf::Color(148, 0, 211))
	{
		color_number = 8;
	}

	return color_number;
}


int TankPlayer::getTankPlayerFigure()
{
	if (TankPlayer::tank_player.getPointCount() == 50)
	{
		figure_number = 50;
	}
	else if (TankPlayer::tank_player.getPointCount() == 3)
	{
		figure_number = 3;
	}
	else if (TankPlayer::tank_player.getPointCount() == 4)
	{
		figure_number = 4;
	}
	else if (TankPlayer::tank_player.getPointCount() == 5)
	{
		figure_number = 5;
	}
	else if (TankPlayer::tank_player.getPointCount() == 6)
	{
		figure_number = 6;
	}
	else if (TankPlayer::tank_player.getPointCount() == 8)
	{
		figure_number = 8;
	}

	return figure_number;
}


void TankPlayer::playerUpgrade(sf::RenderWindow& window, const sf::Event& event)
{
	window.setMouseCursorVisible(true);
	window.clear(sf::Color(200, 200, 200));

	TankPlayer::pause = true;

	std::vector<std::unique_ptr<Button>> upgrade_buttons;

	for (int i = 0; i < 6; ++i)
	{
		sf::RectangleShape number_frame(sf::Vector2f(200, 100));
		number_frame.setPosition(675, 250 + i * 100);
		number_frame.setFillColor(sf::Color::White);
		number_frame.setOutlineColor(sf::Color::Black);
		number_frame.setOutlineThickness(1);

		window.draw(number_frame);
	}

	if (upgrade_buttons.empty())
	{
		upgrade_buttons.emplace_back(std::make_unique<Button>(375, 250, 300, 100, sf::Color(153, 255, 204), sf::Color(102, 255, 178))); //MAX HP
		upgrade_buttons.emplace_back(std::make_unique<Button>(375, 350, 300, 100, sf::Color(102, 255, 178), sf::Color(51, 255, 153))); //PLAYER SPEED
		upgrade_buttons.emplace_back(std::make_unique<Button>(375, 450, 300, 100, sf::Color(51, 255, 153), sf::Color(0, 255, 128))); //PLAYER BODY DAMAGE
		upgrade_buttons.emplace_back(std::make_unique<Button>(375, 550, 300, 100, sf::Color(0, 255, 128), sf::Color(0, 204, 102))); //BULLET DAMAGE
		upgrade_buttons.emplace_back(std::make_unique<Button>(375, 650, 300, 100, sf::Color(0, 204, 102), sf::Color(0, 153, 76))); //BULLET SPEED
		upgrade_buttons.emplace_back(std::make_unique<Button>(375, 750, 300, 100, sf::Color(0, 153, 76), sf::Color(153, 255, 204))); //BULLET FREQUENCY
	}

	Other::writingText(375, 10, 80, 2, "!!!UPGRADES!!!", sf::Color(0, 100, 0), sf::Color::Black, sf::Text::Regular, window);
	Other::writingText(250, 175, 40, 1, "Click on the button to become more powerful!", sf::Color::Black, sf::Color::Black, sf::Text::Regular, window);

	for (int i = 0; i < 6; ++i)
	{
		upgrade_buttons[i]->clickButton(event, window);
	}

	for (int i = 0; i < 6; ++i)
	{
		window.draw(*upgrade_buttons[i]);
	}

	std::stringstream stream;

	stream << std::fixed << std::setprecision(2) << TankPlayer::player_max_health;
	std::string player_max_health_str = stream.str();
	stream.str("");

	stream << std::fixed << std::setprecision(2) << TankPlayer::player_speed;
	std::string player_speed_str = stream.str();
	stream.str("");

	stream << std::fixed << std::setprecision(2) << TankPlayer::player_body_damage;
	std::string player_body_damage_str = stream.str();
	stream.str("");

	stream << std::fixed << std::setprecision(2) << TankPlayer::player_bullet_damage;
	std::string player_bullet_damage_str = stream.str();
	stream.str("");

	stream << std::fixed << std::setprecision(2) << TankPlayer::player_bullet_speed;
	std::string player_bullet_speed_str = stream.str();
	stream.str("");

	stream << std::fixed << std::setprecision(2) << TankPlayer::player_bullet_delay;
	std::string player_bullet_delay_str = stream.str();
	stream.str("");

	Other::writingText(475, 275, 30, 1, "MAX HP", sf::Color::Black, sf::Color::Black, sf::Text::Regular, window);
	Other::writingText(750, 275, 35, 1, player_max_health_str, sf::Color::Black, sf::Color::Black, sf::Text::Regular, window);

	Other::writingText(445, 375, 30, 1, "PLAYER SPEED", sf::Color::Black, sf::Color::Black, sf::Text::Regular, window);
	Other::writingText(750, 375, 35, 1, player_speed_str, sf::Color::Black, sf::Color::Black, sf::Text::Regular, window);

	Other::writingText(435, 475, 30, 1, "BODY DAMAGE", sf::Color::Black, sf::Color::Black, sf::Text::Regular, window);
	Other::writingText(750, 475, 35, 1, player_body_damage_str, sf::Color::Black, sf::Color::Black, sf::Text::Regular, window);

	Other::writingText(425, 575, 30, 1, "BULLET DAMAGE", sf::Color::Black, sf::Color::Black, sf::Text::Regular, window);
	Other::writingText(750, 575, 35, 1, player_bullet_damage_str, sf::Color::Black, sf::Color::Black, sf::Text::Regular, window);

	Other::writingText(445, 675, 30, 1, "BULLET SPEED", sf::Color::Black, sf::Color::Black, sf::Text::Regular, window);
	Other::writingText(750, 675, 35, 1, player_bullet_speed_str, sf::Color::Black, sf::Color::Black, sf::Text::Regular, window);

	Other::writingText(445, 775, 30, 1, "BULLET DELAY", sf::Color::Black, sf::Color::Black, sf::Text::Regular, window);
	Other::writingText(750, 775, 35, 1, player_bullet_delay_str, sf::Color::Black, sf::Color::Black, sf::Text::Regular, window);


	if (upgrade_buttons[0]->isClicked())
	{
		TankPlayer::pause = false;
		TankPlayer::upgrade_selected = true;
		TankPlayer::player_max_health += 2;
		upgrade_buttons[0]->turnOffButton();
	}
	else if (upgrade_buttons[1]->isClicked())
	{
		TankPlayer::pause = false;
		TankPlayer::upgrade_selected = true;
		TankPlayer::player_speed += 5.f;
		upgrade_buttons[1]->turnOffButton();
	}
	else if (upgrade_buttons[2]->isClicked())
	{
		TankPlayer::pause = false;
		TankPlayer::upgrade_selected = true;
		TankPlayer::player_body_damage += 0.5f;
		upgrade_buttons[3]->turnOffButton();
	}
	else if (upgrade_buttons[3]->isClicked())
	{
		TankPlayer::pause = false;
		TankPlayer::upgrade_selected = true;
		TankPlayer::player_bullet_damage += 0.5f;
		upgrade_buttons[3]->turnOffButton();
	}
	else if (upgrade_buttons[4]->isClicked())
	{
		TankPlayer::pause = false;
		TankPlayer::upgrade_selected = true;
		TankPlayer::player_bullet_speed += 1.0f;
		upgrade_buttons[4]->turnOffButton();
	}
	else if (upgrade_buttons[5]->isClicked())
	{
		TankPlayer::pause = false;
		TankPlayer::upgrade_selected = true;

		if (TankPlayer::player_bullet_delay != 0.05f)
		{
			TankPlayer::player_bullet_delay -= 0.05f;
		}
		else
		{
			TankPlayer::player_bullet_delay = 0.05f;
		}
		upgrade_buttons[5]->turnOffButton();
	}
}

