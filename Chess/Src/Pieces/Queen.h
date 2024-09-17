#pragma once

#include "Piece.h"

class Queen : public Piece
{

public:
    Queen(const sf::Texture& texture, const sf::Vector2f& size, Player player);
    ~Queen(){}
    bool CanMove(const sf::Vector2u& position) override;
};