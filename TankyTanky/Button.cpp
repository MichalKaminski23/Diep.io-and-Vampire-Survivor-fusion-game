#include "Button.h"


bool Button::button_clicked = false;
int Button::current_page_index = 0;
std::vector<Page> Button::pages = {};


Button::Button(const int& x, const int& y, const float& width, const float& height, const sf::Color& primary_color, const sf::Color& secondary_color)
	: primary_color(primary_color), secondary_color(secondary_color)
{
	shape.setFillColor(primary_color);
	shape.setPosition(x, y);
	shape.setSize(sf::Vector2f(width, height));
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::Black);

	clicked = false;
}


Button::Button(const int& point_count, const int& x, const int& y, const sf::Color& color)
{
	tank_shape.setRadius(40);
	tank_shape.setPointCount(point_count);
	tank_shape.setPosition(sf::Vector2f(x, y));
	tank_shape.setFillColor(color);
	tank_shape.setOutlineColor(sf::Color::Black);
	tank_shape.setOutlineThickness(2);

	clicked = false;
}


Button::Button(const sf::Vector2f& position, const sf::Vector2f& size) : position(position), size(size), typing(false)
{
	text_box.setSize(size);
	text_box.setFillColor(sf::Color::Green);
	text_box.setOutlineColor(sf::Color::Black);
	text_box.setOutlineThickness(2);
	text_box.setPosition(position);

	clicked = false;
}


void Button::clickButton(const sf::Event& event, sf::RenderWindow& window)
{
	if (button_clicked == false)
	{
		if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
			sf::Vector2f mouse_position_f(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y));

			if (shape.getGlobalBounds().contains(mouse_position_f) or tank_shape.getGlobalBounds().contains(mouse_position_f))
			{
				clicked = true;
				this->onClick(event, window);
			}
			else if (text_box.getGlobalBounds().contains(mouse_position_f))
			{
				clicked = true;
				typing = true;
				text_box.setOutlineColor(sf::Color::Red);
			}
			else
			{
				typing = false;
				text_box.setOutlineColor(sf::Color::Black);
			}
		}
		else if ((event.type == sf::Event::TextEntered or event.type == sf::Event::KeyPressed) and typing == true)
		{
			this->onClick(event, window);
		}
	}

	if (event.type == sf::Event::MouseMoved)
	{
		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_position_f(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y));

		if (shape.getGlobalBounds().contains(mouse_position_f))
		{
			shape.setFillColor(secondary_color);
		}
		else
		{
			shape.setFillColor(primary_color);
		}
	}

	if (event.type == sf::Event::MouseButtonReleased)
	{
		button_clicked = false;
	}
}


void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->shape);
}


bool Button::isClicked() const
{
	return clicked;
}


void Button::onClick(const sf::Event& event, sf::RenderWindow& window)
{
	;
}


void Button::turnOffButton()
{
	clicked = false;
}
