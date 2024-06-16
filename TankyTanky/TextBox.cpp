#include "TextBox.h"


bool TextBox::text_check = false;
std::string TextBox::input_text = "";


void TextBox::onClick(const sf::Event& event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::TextEntered and typing == true)
	{
		bool is_ctrl_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);
		bool is_alt_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt);

		if (!is_ctrl_pressed and !is_alt_pressed)
		{
			char entered_char = static_cast<char>(event.text.unicode);
			std::regex allowed_chars("[a-zA-Z0-9]");

			if (std::regex_match(std::string(1, entered_char), allowed_chars) && input_text.size() < 14)
			{
				input_text += entered_char;
			}
			else if (event.text.unicode == 8 and !input_text.empty())
			{
				input_text.pop_back();
			}
		}
	}
	else if (event.type == sf::Event::KeyPressed and typing == true)
	{
		if (event.key.code == sf::Keyboard::Enter and !input_text.empty())
		{
			std::fstream file("files/players.txt", std::ios::in);
			std::string line;
			std::string text;

			while (std::getline(file, line))
			{
				text += line + "\n";
			}

			std::regex name_regex("^" + input_text + "$");

			auto start = std::sregex_iterator(text.begin(), text.end(), name_regex);
			auto end = std::sregex_iterator();

			bool name_exists = false;

			for (std::sregex_iterator i = start; i != end; i++)
			{
				std::smatch match = *i;
				name_exists = true;
				break;
			}

			file.close();

			if (name_exists)
			{
				typing = false;
				text_check = false;
				text_box.setOutlineColor(sf::Color::Black);
			}
			else
			{
				typing = false;
				text_check = true;
				text_box.setOutlineColor(sf::Color::Black);
			}
		}
	}
}


void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->text_box);

	if (!input_text.empty())
	{
		Other::writingText(position.x + 5.f, position.y + 8.f, size.y * 0.6f, 0.f, input_text, sf::Color::Black, sf::Color::Black, sf::Text::Regular,
			const_cast<sf::RenderWindow&>(static_cast<const sf::RenderWindow&>(target)));
	}
}


void TextBox::clearTextBox()
{
	if (guard == 0)
	{
		input_text.clear();
		guard = 1;
	}
}


