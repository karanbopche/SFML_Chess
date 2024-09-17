#pragma once
#include "ChessState.h"

class PieceSelectedState : public ChessState
{

public:
    PieceSelectedState(ChessContext &context);

    virtual void EnterState() override;
    virtual void ExitState() override;
    virtual void EventHandler(sf::Event &event) override;
    virtual void Update() override;
    virtual void Draw() override;

protected:
    bool isPathBlocked(sf::Vector2u from, sf::Vector2u to);
    void MovePiece(const sf::Vector2u &from, const sf::Vector2u &to);
    void CapturePiece(const sf::Vector2u &piecePosition);
    
    void HighlightPossibleMove(Piece* piece);
};