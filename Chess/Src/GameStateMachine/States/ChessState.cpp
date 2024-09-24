#include "ChessState.h"

ChessState::ChessState(GameContext &context) : HierarchicalState(GameStateKeys::ChessStateKey, context)
{
    this->chessStateMachine = std::make_unique<ChessStateMachine>(context.window);
}

void ChessState::EnterState()
{
    this->chessStateMachine->Start();
}

void ChessState::ExitState()
{
}

void ChessState::EventHandler(sf::Event &event)
{
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        this->SetNextState(GameStateKeys::PauseMenuStateKey);
    this->chessStateMachine->EventHandler(event);
}

void ChessState::Update()
{
    this->chessStateMachine->Update();
}

void ChessState::Draw()
{
    this->chessStateMachine->Draw();
    this->chessStateMachine->StateTransition();
}
