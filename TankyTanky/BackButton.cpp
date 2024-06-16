#include "BackButton.h"


void BackButton::onClick(const sf::Event& event, sf::RenderWindow& window)
{
    if (Button::current_page_index > 0)
    {
        Button::current_page_index--;
        button_clicked = true;
    }
}
