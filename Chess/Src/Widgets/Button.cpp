#include "Button.h"


Button::Button(const std::string& text, const sf::Font& font)
{
    this->text.setString(text);
    this->text.setFont(font);
    this->text.setColor(sf::Color::Black);
}

void Button::EventHandler(sf::Event& event, sf::RenderWindow& window)
{
    if(event.type == sf::Event::MouseButtonReleased)
    {
        auto mousePos = sf::Mouse::getPosition(window)
    }
}

void Button::Draw(sf::RenderWindow* window)
{
    window->draw(this->text);
}
