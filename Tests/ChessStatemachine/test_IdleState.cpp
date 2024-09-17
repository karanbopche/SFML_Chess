#include <gtest/gtest.h>
#include <ChessStateMachine/States/IdleState.h>
#include <mocks/Pieces/Piece_Mock.h>

class IdleState_Fixture : public IdleState, public testing::Test
{
public:
    IdleState_Fixture(): IdleState(context)
    {
        for(auto &row : this->context.pieces)
            for(auto &piece : row)
                piece = nullptr;
    }

    ChessContext context;
};

TEST_F(IdleState_Fixture, is_valid_selection_empty_board)
{
    for(unsigned int row=0;row<this->context.VERTICAL_BOXES;row++)
    for(unsigned int col=0;col<this->context.HORIZONTAL_BOXES;col++)
    {
        ASSERT_EQ(this->IsValidSelection({col, row}), false);
    }
}

TEST_F(IdleState_Fixture, is_valid_selection)
{
    sf::Texture texture;

    auto piece = Piece_Mock(texture, {10, 10}, Player::PLAYER_1, PieceType::Pawn);
    context.pieces[0][0] = &piece;
    ASSERT_EQ(this->IsValidSelection({0, 0}), true);
    ASSERT_EQ(this->IsValidSelection({0, 1}), false);
}
