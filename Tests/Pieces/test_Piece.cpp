#include <gtest/gtest.h>
#include "Pieces/Piece.h"

class Test_Piece : public Piece
{
public:
    Test_Piece(const sf::Texture& texture, const sf::Vector2f& size, const Player player) : Piece(texture, size, player, PieceType::Pawn) {}
    bool CanMove(const sf::Vector2u& location) override {return true;}
};



TEST(PIECE_SUITE, Initialization)
{
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    
    auto piece = Test_Piece(texture, size, Player::PLAYER_1);

    ASSERT_EQ(piece.GetPlayer(), Player::PLAYER_1);
}