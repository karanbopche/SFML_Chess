#pragma once

#include <StateMachine/HierarchicalState.h>
#include "../GameStateMachine.h"
#include <ChessStateMachine/ChessStateMachine.h>


class ChessState: public HierarchicalState<GameStateKeys, GameContext>
{
public:
    explicit ChessState(GameContext &context);
    virtual void EnterState() override;
    virtual void ExitState() override;
    virtual void EventHandler(sf::Event &event) override;
    virtual void Update() override;
    virtual void Draw() override;
protected:
    std::unique_ptr<ChessStateMachine> chessStateMachine;
};