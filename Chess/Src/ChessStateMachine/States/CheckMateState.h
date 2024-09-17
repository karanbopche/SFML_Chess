#pragma once
#include "ChessState.h"


class CheckMateState : public ChessState
{
public:
    CheckMateState(ChessContext& context) : ChessState(context, ChessStateKeys::CheckMateStateKey){}
    virtual void EnterState() override;
    virtual void ExitState() override;
    virtual void EventHandler(sf::Event& event) override;
    virtual void Update() override;
    virtual void Draw() override; 
protected:
    sf::Text gameOver;
};
