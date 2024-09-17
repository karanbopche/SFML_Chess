#pragma once
#include "ChessState.h"


class CheckState : public ChessState
{
public:
    CheckState(ChessContext& context) : ChessState(context, ChessStateKeys::CheckStateKey){} 
    virtual void EnterState() override;
    virtual void ExitState() override;
    virtual void EventHandler(sf::Event& event) override;
    virtual void Update() override;
    virtual void Draw() override; 
protected:
    int GetCheckCount();
    bool CanAvoidAttackByMoving(Piece *piece);
    bool CanBlockPath(sf::Vector2u from, sf::Vector2u to, Player player);
    bool IsUnderCheck();
};
