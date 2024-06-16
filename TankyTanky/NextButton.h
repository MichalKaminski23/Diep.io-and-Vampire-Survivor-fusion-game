#pragma once


#include "Button.h"


class NextButton : public Button 
{
public:

    using Button::Button;

    void onClick(const sf::Event& event, sf::RenderWindow& window) override;
    
};
