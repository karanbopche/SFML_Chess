#include "CheckMateState.h"
#include <Manager/FontManager.h>


void CheckMateState::EnterState()
{
    this->gameOver.setFont(FontManager::GetInstance()->GetItem("default"));
    this->gameOver.setString("Game Over");
    this->gameOver.setCharacterSize(100);
    this->gameOver.setFillColor(sf::Color::Red);
    auto textCenter = this->gameOver.getLocalBounds().getSize()/2.f;
    auto windowCenter = this->context.window->getSize()/2U;
    const sf::Vector2f& textPos = {
        windowCenter.x - textCenter.x,
        windowCenter.y - textCenter.y
    };
    this->gameOver.setPosition(textPos);
}

void CheckMateState::ExitState()
{
}

void CheckMateState::EventHandler(sf::Event &event)
{
}

void CheckMateState::Update()
{
}

void CheckMateState::Draw()
{
    this->context.window->draw(this->gameOver);
}
