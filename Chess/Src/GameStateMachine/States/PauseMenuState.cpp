#include "PauseMenuState.h"

PauseMenuState::PauseMenuState(GameContext &context) : HierarchicalState(GameStateKeys::ChessStateKey, context)
{
}

void PauseMenuState::EnterState()
{
}

void PauseMenuState::ExitState()
{
}

void PauseMenuState::EventHandler(sf::Event &event)
{
    if(event.type == sf::Event::KeyReleased)
    {
        if(event.key.code == sf::Keyboard::Escape)
            this->SetNextState(GameStateKeys::ChessStateKey);
    }

}

void PauseMenuState::Update()
{
}

void PauseMenuState::Draw()
{
}
