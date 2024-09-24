#include <Config.h>
#include "GameStateMachine.h"
#include "States/ChessState.h"
#include "States/MainMenuState.h"
#include "States/PauseMenuState.h"

GameStateMachine::GameStateMachine(sf::RenderWindow *window)
{
    this->context.window = window;
    this->InitStates();
}

void GameStateMachine::InitStates()
{
    this->RegisterState(GameStateKeys::MainMenuStateKey, std::move(std::make_unique<MainMenuState>(this->context)));
    this->RegisterState(GameStateKeys::ChessStateKey, std::move(std::make_unique<ChessState>(this->context)));
    this->RegisterState(GameStateKeys::PauseMenuStateKey, std::move(std::make_unique<PauseMenuState>(this->context)));

    this->currentState = GameStateKeys::MainMenuStateKey;
}
