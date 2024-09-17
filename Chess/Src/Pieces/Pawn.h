#pragma once

#include "Piece.h"

class Pawn : public Piece
{

public:
    Pawn(const sf::Texture& texture, const sf::Vector2f& size, Player player);
    ~Pawn(){}
    bool CanMove(const sf::Vector2u& position) override;
};