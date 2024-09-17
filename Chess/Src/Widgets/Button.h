#pragma once

#include <string>
#include <functional>
#include <SFML/Graphics.hpp>

class Button
{
public:
    using Callback = std::function<void(void)>;
    Button(const std::string& text, const sf::Font& font);
    ~Button() = default;
    void EventHandler(sf::Event& event, sf::RenderWindow* window);
    void Draw(sf::RenderWindow* window);

    const sf::Vector2f& GetPosition() {return this->text.getPosition();}
    void SetPosition(const sf::Vector2f& position) { this->text.setPosition(position);}
    void SetFont(const sf::Font& font) { this->text.setFont(font);}
    void SetOnClickCallback(Callback callback) {this->onClick = callback;}
    void SetOnFocusCallback(Callback callback) {this->onFocus = callback;}



protected:
    sf::Text text;
    Callback onClick;
    Callback onFocus;
};