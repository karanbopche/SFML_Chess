#pragma once

#include "../ChessStateMachine.h"

class ChessState : public HierarchicalState<ChessStateKeys>
{
public:
    inline ChessState(ChessContext &context, ChessStateKeys key) : HierarchicalState(key), context(context) {}
    bool IsValidMove(const sf::Vector2u &from, const sf::Vector2u &to, Player player);
    bool isPathBlocked(sf::Vector2u from, sf::Vector2u to);
    inline void SwitchPlayer()
    {
        if (this->context.currentPlayer == Player::PLAYER_1)
            this->context.currentPlayer = Player::PLAYER_2;
        else
            this->context.currentPlayer = Player::PLAYER_1;
    }
    Piece *FindKing(Player player);
    std::vector<Piece *> GetAttackers(Player player, const sf::Vector2u &position);

protected:
    ChessContext &context;
};
