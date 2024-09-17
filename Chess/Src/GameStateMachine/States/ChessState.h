#pragma once

#include "GameState.h"
#include <ChessStateMachine/ChessStateMachine.h>

class ChessState: public GameState
{
public:
    explicit ChessState(GameContext &context);
    virtual void EnterState() override;
    virtual void ExitState() override;
    virtual void EventHandler(sf::Event &event) override;
    virtual void Update() override;
    virtual void Draw() override;
    virtual void SuspendState() override;
    virtual void WakeUpState() override;

protected:
    ChessStateMachine *chessStateMachine;
};