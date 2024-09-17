#pragma once

#include "Piece.h"

class King : public Piece
{

public:
    King(const sf::Texture& texture, const sf::Vector2f& size, Player player);
    ~King(){}
    bool CanMove(const sf::Vector2u& position) override;
};