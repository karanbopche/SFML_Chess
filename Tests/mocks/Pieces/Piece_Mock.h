#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Pieces/Piece.h>


class Piece_Mock: public Piece
{
public:
    Piece_Mock(const sf::Texture &texture, const sf::Vector2f &size, const Player player, const PieceType type) : Piece(texture, size, player, type){}
    MOCK_METHOD(bool, CanMove, (const sf::Vector2u&));
};
