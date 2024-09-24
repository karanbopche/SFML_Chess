#include "Button.h"

Button::Button()
{
    this->text.setFillColor(sf::Color::Red);
    this->text.setCharacterSize(100);
    this->background.setFillColor(sf::Color::Blue);
}

Button::Button(const std::string &text, const sf::Font &font) : Button()
{
    this->SetText(text);
    this->text.setFont(font);
}

void Button::EventHandler(sf::Event &event)
{
    auto buttonRect = this->text.getGlobalBounds();
    if (event.type == sf::Event::MouseButtonReleased)
    {
        if (this->background.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
            if (this->onClick)
                this->onClick();
    }
    if (event.type == sf::Event::MouseMoved)
    {
        if (this->background.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
        {
            this->text.setStyle(sf::Text::Bold | sf::Text::Underlined);
            if (this->onFocus)
                this->onFocus();
        }
        else
        {
            this->text.setStyle(sf::Text::Regular);
        }
    }
}

void Button::Draw(sf::RenderWindow *window)
{
    window->draw(this->background);
    window->draw(this->text);
}

void Button::SetPosition(const sf::Vector2f &position)
{
    this->background.setPosition(position);
    this->text.setPosition(position);
}

void Button::SetText(const std::string &text)
{
    this->text.setString(text);
    const auto &bound = this->text.getGlobalBounds();
    this->background.setSize(bound.getSize()*1.3f);
}

void Button::SetOriginToCenter()
{
    auto center = this->background.getSize()/2.0f;
    this->background.setOrigin(center);
    this->background.setOrigin(center);
}