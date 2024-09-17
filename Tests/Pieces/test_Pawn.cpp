#include <gtest/gtest.h>
#include "Pieces/Pawn.h"


static void checkRange(Pawn &pawn, const sf::Vector2u &startPosition, const sf::Vector2i &delta, bool expected, const sf::Vector2u *excludeList = nullptr, size_t excludeListSize = 0)
{
    pawn.SetToBox(startPosition);
    sf::Vector2u testPosition = startPosition;
    
    /* no delta, creates infinite loop */
    ASSERT_FALSE(delta.x == 0 && delta.y == 0);
    
    /* can not move to start position */
    ASSERT_EQ(pawn.CanMove(testPosition), false);

    do
    {
        testPosition.x = testPosition.x + delta.x;
        testPosition.y = testPosition.y + delta.y;
        bool skipCheck = false;

        for (size_t i = 0; i < excludeListSize; i++)
            skipCheck |= (excludeList && excludeList[i] == testPosition);

        if (!skipCheck)
            ASSERT_EQ(pawn.CanMove(testPosition), expected);
    } while (testPosition.x > 0 && testPosition.y > 0 && testPosition.x < 7 && testPosition.y < 7);
}

TEST(PAWN_SUITE, pawn_player_1_movement_backwards)
{
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    sf::Vector2u position = {6, 6};
    bool expect = false;
    
    auto pawn = Pawn(texture, size, Player::PLAYER_1);
    pawn.SetToBox(position);
    ASSERT_EQ(pawn.CanMove({position.x, position.y+1}), expect);
}

TEST(PAWN_SUITE, pawn_player_1_movement_Initial)
{
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    sf::Vector2u position = {6, 6};
    bool expect = true;
    
    auto pawn = Pawn(texture, size, Player::PLAYER_1);
    pawn.SetToBox(position);
    ASSERT_EQ(pawn.CanMove({position.x, position.y-1}), expect);
    ASSERT_EQ(pawn.CanMove({position.x, position.y-2}), expect);
    ASSERT_EQ(pawn.CanMove({position.x+1, position.y-1}), expect);
    ASSERT_EQ(pawn.CanMove({position.x-1, position.y-1}), expect);
}

TEST(PAWN_SUITE, pawn_player_1_movement_after_moved)
{
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    sf::Vector2u position = {4, 1};
    
    auto pawn = Pawn(texture, size, Player::PLAYER_1);
    pawn.SetToBox(position);
    ASSERT_EQ(pawn.CanMove({position.x, position.y-1}), true);
    ASSERT_EQ(pawn.CanMove({position.x+1, position.y-1}), true);
    ASSERT_EQ(pawn.CanMove({position.x-1, position.y-1}), true);
}

TEST(PAWN_SUITE, pawn_player_1_movement_vertical_up)
{
    const sf::Vector2u &startPosition = {0, 7};
    const sf::Vector2i &delta = {0, -1};
    bool expected = false;
    const sf::Vector2u excludeList[] =
    {
        /* exclude immediate above box */
        {startPosition.x + delta.x, startPosition.y + delta.y},
    };

    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto pawn = Pawn(texture, size, Player::PLAYER_1);

    checkRange(
        pawn,
        startPosition,
        delta,
        expected,
        excludeList,
        sizeof(excludeList) / sizeof(excludeList));
}

TEST(PAWN_SUITE, pawn_player_1_movement_vertical_down)
{
    const sf::Vector2u &startPosition = {0, 0};
    const sf::Vector2i &delta = {0, 1};
    bool expected = false;
    

    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto pawn = Pawn(texture, size, Player::PLAYER_1);

    checkRange(
        pawn,
        startPosition,
        delta,
        expected);
}

TEST(PAWN_SUITE, pawn_player_1_movement_horizontal_left)
{
    const sf::Vector2u &startPosition = {7, 0};
    const sf::Vector2i &delta = {-1, 0};
    bool expected = false;
    
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto pawn = Pawn(texture, size, Player::PLAYER_1);

    checkRange(
        pawn,
        startPosition,
        delta,
        expected);
}

TEST(PAWN_SUITE, pawn_player_1_movement_horizontal_right)
{
    const sf::Vector2u &startPosition = {0, 0};
    const sf::Vector2i &delta = {1, 0};
    bool expected = false;
    
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto pawn = Pawn(texture, size, Player::PLAYER_1);

    checkRange(
        pawn,
        startPosition,
        delta,
        expected);
}

TEST(PAWN_SUITE, pawn_player_1_movement_diagonal_bottom_right)
{
    const sf::Vector2u &startPosition = {0, 0};
    const sf::Vector2i &delta = {1, 1};
    bool expected = false;
    
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto pawn = Pawn(texture, size, Player::PLAYER_1);

    checkRange(
        pawn,
        startPosition,
        delta,
        expected);
}

TEST(PAWN_SUITE, pawn_player_1_movement_diagonal_bottom_left)
{
    const sf::Vector2u &startPosition = {7, 0};
    const sf::Vector2i &delta = {-1, 1};
    bool expected = false;
    
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto pawn = Pawn(texture, size, Player::PLAYER_1);

    checkRange(
        pawn,
        startPosition,
        delta,
        expected);
}

TEST(PAWN_SUITE, pawn_player_1_movement_diagonal_top_right)
{
    const sf::Vector2u &startPosition = {0, 7};
    const sf::Vector2i &delta = {1, -1};
    bool expected = false;
    const sf::Vector2u excludeList[] =
        {
        {startPosition.x + delta.x, startPosition.y + delta.y}
        };
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto pawn = Pawn(texture, size, Player::PLAYER_1);

    checkRange(
        pawn,
        startPosition,
        delta,
        expected,
        excludeList,
        sizeof(excludeList) / sizeof(excludeList));
}

TEST(PAWN_SUITE, pawn_player_1_movement_diagonal_top_left)
{
    const sf::Vector2u &startPosition = {7, 7};
    const sf::Vector2i &delta = {-1, -1};
    bool expected = false;
    const sf::Vector2u excludeList[] =
        {
        {startPosition.x + delta.x, startPosition.y + delta.y}
        };
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto pawn = Pawn(texture, size, Player::PLAYER_1);

    checkRange(
        pawn,
        startPosition,
        delta,
        expected,
        excludeList,
        sizeof(excludeList) / sizeof(excludeList));
}

TEST(PAWN_SUITE, pawn_player_1_movement_nearby)
{
    const sf::Vector2u &startPosition = {3, 3};

    sf::Texture texture;
    sf::Vector2f size = {10, 10};

    auto pawn = Pawn(texture, size, Player::PLAYER_1);
    pawn.SetToBox(startPosition);

    ASSERT_EQ(pawn.CanMove({startPosition.x - 1, startPosition.y}), false);
    ASSERT_EQ(pawn.CanMove({startPosition.x + 1, startPosition.y}), false);
    ASSERT_EQ(pawn.CanMove({startPosition.x, startPosition.y - 1}), true);
    ASSERT_EQ(pawn.CanMove({startPosition.x, startPosition.y + 1}), false);
}

TEST(PAWN_SUITE, pawn_player_1_movement_nearby_diagonal)
{
    const sf::Vector2u &startPosition = {3, 3};

    sf::Texture texture;
    sf::Vector2f size = {10, 10};

    auto pawn = Pawn(texture, size, Player::PLAYER_1);
    pawn.SetToBox(startPosition);

    ASSERT_EQ(pawn.CanMove({startPosition.x + 1, startPosition.y + 1}), false);
    ASSERT_EQ(pawn.CanMove({startPosition.x + 1, startPosition.y - 1}), true);
    ASSERT_EQ(pawn.CanMove({startPosition.x - 1, startPosition.y + 1}), false);
    ASSERT_EQ(pawn.CanMove({startPosition.x - 1, startPosition.y - 1}), true);
}

TEST(PAWN_SUITE, pawn_player_1_movement_two_and_half)
{
    const sf::Vector2u &startPosition = {3, 3};
    bool expected = false;

    sf::Texture texture;
    sf::Vector2f size = {10, 10};

    auto pawn = Pawn(texture, size, Player::PLAYER_1);
    pawn.SetToBox(startPosition);

    ASSERT_EQ(pawn.CanMove({startPosition.x + 2, startPosition.y + 1}), expected);
    ASSERT_EQ(pawn.CanMove({startPosition.x - 2, startPosition.y + 1}), expected);
    ASSERT_EQ(pawn.CanMove({startPosition.x + 2, startPosition.y - 1}), expected);
    ASSERT_EQ(pawn.CanMove({startPosition.x - 2, startPosition.y - 1}), expected);
    ASSERT_EQ(pawn.CanMove({startPosition.x + 1, startPosition.y + 2}), expected);
    ASSERT_EQ(pawn.CanMove({startPosition.x - 1, startPosition.y + 2}), expected);
    ASSERT_EQ(pawn.CanMove({startPosition.x + 1, startPosition.y - 2}), expected);
    ASSERT_EQ(pawn.CanMove({startPosition.x - 1, startPosition.y - 2}), expected);
}

TEST(PAWN_SUITE, pawn_player_2_movement_backwards)
{
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    sf::Vector2u position = {6, 2};
    bool expect = false;

    auto pawn = Pawn(texture, size, Player::PLAYER_2);
    pawn.SetToBox(position);
    ASSERT_EQ(pawn.CanMove({position.x, position.y-1}), expect);
    ASSERT_EQ(pawn.CanMove({position.x, position.y-2}), expect);
}

TEST(PAWN_SUITE, pawn_player_2_movement_Initial)
{
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    sf::Vector2u position = {6, 1};
    bool expect = true;
    
    auto pawn = Pawn(texture, size, Player::PLAYER_2);
    pawn.SetToBox(position);
    ASSERT_EQ(pawn.CanMove({position.x, position.y+1}), expect);
    ASSERT_EQ(pawn.CanMove({position.x, position.y+2}), expect);
    ASSERT_EQ(pawn.CanMove({position.x+1, position.y+1}), expect);
    ASSERT_EQ(pawn.CanMove({position.x-1, position.y+1}), expect);
}

TEST(PAWN_SUITE, pawn_player_2_movement_after_moved)
{
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    sf::Vector2u position = {4, 1};
    
    auto pawn = Pawn(texture, size, Player::PLAYER_2);
    pawn.SetToBox(position);
    ASSERT_EQ(pawn.CanMove({position.x, position.y+1}), true);
    ASSERT_EQ(pawn.CanMove({position.x+1, position.y+1}), true);
    ASSERT_EQ(pawn.CanMove({position.x-1, position.y+1}), true);
}

TEST(PAWN_SUITE, pawn_player_2_movement_vertical_up)
{
    const sf::Vector2u &startPosition = {0, 7};
    const sf::Vector2i &delta = {0, -1};
    bool expected = false;
    const sf::Vector2u excludeList[] =
    {
        /* exclude immediate above box */
        {startPosition.x + delta.x, startPosition.y + delta.y},
    };

    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto pawn = Pawn(texture, size, Player::PLAYER_2);

    checkRange(
        pawn,
        startPosition,
        delta,
        expected,
        excludeList,
        sizeof(excludeList) / sizeof(excludeList));
}

TEST(PAWN_SUITE, pawn_player_2_movement_vertical_down)
{
    const sf::Vector2u &startPosition = {0, 0};
    const sf::Vector2i &delta = {0, 1};
    bool expected = false;
    const sf::Vector2u excludeList[] =
    {
        /* exclude immediate below box */
        {startPosition.x + delta.x, startPosition.y + delta.y},
    };

    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto pawn = Pawn(texture, size, Player::PLAYER_2);

    checkRange(
        pawn,
        startPosition,
        delta,
        expected,
        excludeList,
        sizeof(excludeList) / sizeof(excludeList));
}

TEST(PAWN_SUITE, pawn_player_2_movement_horizontal_left)
{
    const sf::Vector2u &startPosition = {7, 0};
    const sf::Vector2i &delta = {-1, 0};
    bool expected = false;
    
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto pawn = Pawn(texture, size, Player::PLAYER_2);

    checkRange(
        pawn,
        startPosition,
        delta,
        expected);
}

TEST(PAWN_SUITE, pawn_player_2_movement_horizontal_right)
{
    const sf::Vector2u &startPosition = {0, 0};
    const sf::Vector2i &delta = {1, 0};
    bool expected = false;
    
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto pawn = Pawn(texture, size, Player::PLAYER_2);

    checkRange(
        pawn,
        startPosition,
        delta,
        expected);
}

TEST(PAWN_SUITE, pawn_player_2_movement_diagonal_bottom_right)
{
    const sf::Vector2u &startPosition = {0, 0};
    const sf::Vector2i &delta = {1, 1};
    bool expected = false;
    const sf::Vector2u excludeList[] =
        {
        {startPosition.x + delta.x, startPosition.y + delta.y}
        };
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto pawn = Pawn(texture, size, Player::PLAYER_2);

    checkRange(
        pawn,
        startPosition,
        delta,
        expected,
        excludeList,
        sizeof(excludeList) / sizeof(excludeList));
}

TEST(PAWN_SUITE, pawn_player_2_movement_diagonal_bottom_left)
{
    const sf::Vector2u &startPosition = {7, 0};
    const sf::Vector2i &delta = {-1, 1};
    bool expected = false;
    const sf::Vector2u excludeList[] =
        {
        {startPosition.x + delta.x, startPosition.y + delta.y}
        };
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto pawn = Pawn(texture, size, Player::PLAYER_2);

    checkRange(
        pawn,
        startPosition,
        delta,
        expected,
        excludeList,
        sizeof(excludeList) / sizeof(excludeList));
}

TEST(PAWN_SUITE, pawn_player_2_movement_diagonal_top_right)
{
    const sf::Vector2u &startPosition = {0, 7};
    const sf::Vector2i &delta = {1, -1};
    bool expected = false;
    
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto pawn = Pawn(texture, size, Player::PLAYER_2);

    checkRange(
        pawn,
        startPosition,
        delta,
        expected);
}

TEST(PAWN_SUITE, pawn_player_2_movement_diagonal_top_left)
{
    const sf::Vector2u &startPosition = {7, 7};
    const sf::Vector2i &delta = {-1, -1};
    bool expected = false;
    
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto pawn = Pawn(texture, size, Player::PLAYER_2);

    checkRange(
        pawn,
        startPosition,
        delta,
        expected);
}

TEST(PAWN_SUITE, pawn_player_2_movement_nearby)
{
    const sf::Vector2u &startPosition = {3, 3};

    sf::Texture texture;
    sf::Vector2f size = {10, 10};

    auto pawn = Pawn(texture, size, Player::PLAYER_2);
    pawn.SetToBox(startPosition);

    ASSERT_EQ(pawn.CanMove({startPosition.x - 1, startPosition.y}), false);
    ASSERT_EQ(pawn.CanMove({startPosition.x + 1, startPosition.y}), false);
    ASSERT_EQ(pawn.CanMove({startPosition.x, startPosition.y - 1}), false);
    ASSERT_EQ(pawn.CanMove({startPosition.x, startPosition.y + 1}), true);
}

TEST(PAWN_SUITE, pawn_player_2_movement_nearby_diagonal)
{
    const sf::Vector2u &startPosition = {3, 3};

    sf::Texture texture;
    sf::Vector2f size = {10, 10};

    auto pawn = Pawn(texture, size, Player::PLAYER_2);
    pawn.SetToBox(startPosition);

    ASSERT_EQ(pawn.CanMove({startPosition.x + 1, startPosition.y + 1}), true);
    ASSERT_EQ(pawn.CanMove({startPosition.x + 1, startPosition.y - 1}), false);
    ASSERT_EQ(pawn.CanMove({startPosition.x - 1, startPosition.y + 1}), true);
    ASSERT_EQ(pawn.CanMove({startPosition.x - 1, startPosition.y - 1}), false);
}

TEST(PAWN_SUITE, pawn_player_2_movement_two_and_half)
{
    const sf::Vector2u &startPosition = {3, 3};
    bool expected = false;

    sf::Texture texture;
    sf::Vector2f size = {10, 10};

    auto pawn = Pawn(texture, size, Player::PLAYER_2);
    pawn.SetToBox(startPosition);

    ASSERT_EQ(pawn.CanMove({startPosition.x + 2, startPosition.y + 1}), expected);
    ASSERT_EQ(pawn.CanMove({startPosition.x - 2, startPosition.y + 1}), expected);
    ASSERT_EQ(pawn.CanMove({startPosition.x + 2, startPosition.y - 1}), expected);
    ASSERT_EQ(pawn.CanMove({startPosition.x - 2, startPosition.y - 1}), expected);
    ASSERT_EQ(pawn.CanMove({startPosition.x + 1, startPosition.y + 2}), expected);
    ASSERT_EQ(pawn.CanMove({startPosition.x - 1, startPosition.y + 2}), expected);
    ASSERT_EQ(pawn.CanMove({startPosition.x + 1, startPosition.y - 2}), expected);
    ASSERT_EQ(pawn.CanMove({startPosition.x - 1, startPosition.y - 2}), expected);
}
