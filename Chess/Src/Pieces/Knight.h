#pragma once

#include "Piece.h"

class Knight : public Piece
{

public:
    Knight(const sf::Texture& texture, const sf::Vector2f& size, Player player);
    ~Knight(){}
    bool CanMove(const sf::Vector2u& position) override;
};