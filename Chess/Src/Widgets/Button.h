#pragma once

#include <string>
#include <functional>
#include <SFML/Graphics.hpp>

class Button
{
public:
    using Callback = std::function<void(void)>;
    explicit Button();
    Button(const std::string &text, const sf::Font &font);
    ~Button() = default;
    void EventHandler(sf::Event &event);
    void Draw(sf::RenderWindow *window);
    void SetPosition(const sf::Vector2f &position);
    void SetText(const std::string &text);
    void SetOriginToCenter();

    inline const sf::Vector2f &GetPosition() { return this->text.getPosition(); }
    inline void SetFont(const sf::Font &font) { this->text.setFont(font); }
    inline void SetOnClickCallback(Callback callback) { this->onClick = callback; }
    inline void SetOnFocusCallback(Callback callback) { this->onFocus = callback; }

    void SetBackgroundColor(const sf::Color &color) { this->background.setFillColor(color); }
    void SetTextColor(const sf::Color &color) { this->text.setFillColor(color); }
    void SetBorderColor(const sf::Color &color) { this->background.setOutlineColor(color); }
    void SetTextSize(unsigned int size)
    {
        this->text.setCharacterSize(size);
        const auto &bound = this->text.getGlobalBounds();
        this->background.setSize(bound.getSize());
    }

protected:
    sf::Text text;
    sf::RectangleShape background;
    Callback onClick;
    Callback onFocus;
};