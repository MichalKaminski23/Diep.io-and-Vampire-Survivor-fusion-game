#pragma once


#include "ClickableObject.h"
#include "Drawing.h"
#include "Other.h"
#include "Struct.h"


class Button : public Drawing, public ClickableObject
{
public:

	Button(const int& x, const int& y, const float& width, const float& height, const sf::Color& primary_color, const sf::Color& secondary_color);

	Button(const int& point_count, const int& x, const int& y, const sf::Color& color);

	Button(const sf::Vector2f& position, const sf::Vector2f& size);

	~Button() = default;

	void clickButton(const sf::Event& event, sf::RenderWindow& window);

	void turnOffButton();

	bool isClicked() const;

	static bool button_clicked;

	static int current_page_index;

	static std::vector<Page> pages;

	bool clicked = false;

	bool typing = false;

	static sf::CircleShape tank_shape_copy;

	sf::CircleShape tank_shape;

	sf::RectangleShape shape;

	sf::Vector2f position;

	sf::Vector2f size;

	sf::RectangleShape text_box;

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual void onClick(const sf::Event& event, sf::RenderWindow& window) override;

	sf::Color primary_color;

	sf::Color secondary_color;
};

