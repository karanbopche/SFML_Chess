#pragma once

#include "Piece.h"

class Bishop : public Piece
{

public:
    Bishop(const sf::Texture& texture, const sf::Vector2f& size, Player player);
    ~Bishop(){}
    virtual bool CanMove(const sf::Vector2u& position) override;
};