#include "NextButton.h"


void NextButton::onClick(const sf::Event& event, sf::RenderWindow& window)
{
    if (Button::current_page_index < Button::pages.size() - 1)
    {
        Button::current_page_index++;
        button_clicked = true;
    }
}

