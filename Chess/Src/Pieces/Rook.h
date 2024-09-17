#pragma once

#include "Piece.h"

class Rook : public Piece
{

public:
    Rook(const sf::Texture& texture, const sf::Vector2f& size, Player player);
    ~Rook(){}
    bool CanMove(const sf::Vector2u& position) override;
};