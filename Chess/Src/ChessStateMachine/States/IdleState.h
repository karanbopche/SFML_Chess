#pragma once

#include "ChessState.h"


class IdleState : public ChessState
{
public:
    IdleState(ChessContext &context) : ChessState(context, ChessStateKeys::IdleStateKey){}
    virtual void EnterState() override;
    virtual void ExitState() override;
    virtual void EventHandler(sf::Event& event) override;
    virtual void Update() override;
    virtual void Draw() override; 

protected:
    bool IsValidSelection(const sf::Vector2u &position);
};
