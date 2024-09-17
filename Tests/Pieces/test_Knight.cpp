#include <gtest/gtest.h>
#include "Pieces/Knight.h"

static void checkRange(Knight &knight, const sf::Vector2u &startPosition, const sf::Vector2i &delta, bool expected, const sf::Vector2u *excludeList = nullptr, size_t excludeListSize = 0)
{
    knight.SetToBox(startPosition);
    sf::Vector2u testPosition = startPosition;
    
    /* no delta, creates infinite loop */
    ASSERT_FALSE(delta.x == 0 && delta.y == 0);
    
    /* can not move to start position */
    ASSERT_EQ(knight.CanMove(testPosition), false);

    do
    {
        testPosition.x = testPosition.x + delta.x;
        testPosition.y = testPosition.y + delta.y;
        bool skipCheck = false;

        for (size_t i = 0; i < excludeListSize; i++)
            skipCheck |= (excludeList && excludeList[i] == testPosition);

        if (!skipCheck)
            ASSERT_EQ(knight.CanMove(testPosition), expected);
    } while (testPosition.x > 0 && testPosition.y > 0 && testPosition.x < 7 && testPosition.y < 7);
}

TEST(KNIGHT_SUITE, Initialization)
{
    sf::Texture texture;
    sf::Vector2f size = {10, 10};

    auto knight = Knight(texture, size, Player::PLAYER_1);

    ASSERT_EQ(knight.GetPlayer(), Player::PLAYER_1);
}


TEST(KNIGHT_SUITE, knight_movement_vertical_up)
{
    const sf::Vector2u &startPosition = {0, 7};
    const sf::Vector2i &delta = {0, -1};
    bool expected = false;
    
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto knight = Knight(texture, size, Player::PLAYER_1);

    checkRange(
        knight,
        startPosition,
        delta,
        expected);
}

TEST(KNIGHT_SUITE, knight_movement_vertical_down)
{
    const sf::Vector2u &startPosition = {0, 0};
    const sf::Vector2i &delta = {0, 1};
    bool expected = false;
    

    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto knight = Knight(texture, size, Player::PLAYER_1);

    checkRange(
        knight,
        startPosition,
        delta,
        expected);
}

TEST(KNIGHT_SUITE, knight_movement_horizontal_left)
{
    const sf::Vector2u &startPosition = {7, 0};
    const sf::Vector2i &delta = {-1, 0};
    bool expected = false;
    
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto knight = Knight(texture, size, Player::PLAYER_1);

    checkRange(
        knight,
        startPosition,
        delta,
        expected);
}

TEST(KNIGHT_SUITE, knight_movement_horizontal_right)
{
    const sf::Vector2u &startPosition = {0, 0};
    const sf::Vector2i &delta = {1, 0};
    bool expected = false;
    
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto knight = Knight(texture, size, Player::PLAYER_1);

    checkRange(
        knight,
        startPosition,
        delta,
        expected);
}

TEST(KNIGHT_SUITE, knight_movement_diagonal_bottom_right)
{
    const sf::Vector2u &startPosition = {0, 0};
    const sf::Vector2i &delta = {1, 1};
    bool expected = false;
    
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto knight = Knight(texture, size, Player::PLAYER_1);

    checkRange(
        knight,
        startPosition,
        delta,
        expected);
}

TEST(KNIGHT_SUITE, knight_movement_diagonal_bottom_left)
{
    const sf::Vector2u &startPosition = {7, 0};
    const sf::Vector2i &delta = {-1, 1};
    bool expected = false;
    
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto knight = Knight(texture, size, Player::PLAYER_1);

    checkRange(
        knight,
        startPosition,
        delta,
        expected);
}

TEST(KNIGHT_SUITE, knight_movement_diagonal_top_right)
{
    const sf::Vector2u &startPosition = {0, 7};
    const sf::Vector2i &delta = {1, -1};
    bool expected = false;
    
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto knight = Knight(texture, size, Player::PLAYER_1);

    checkRange(
        knight,
        startPosition,
        delta,
        expected);
}

TEST(KNIGHT_SUITE, knight_movement_diagonal_top_left)
{
    const sf::Vector2u &startPosition = {7, 7};
    const sf::Vector2i &delta = {-1, -1};
    bool expected = false;
    
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto knight = Knight(texture, size, Player::PLAYER_1);

    checkRange(
        knight,
        startPosition,
        delta,
        expected);
}

TEST(KNIGHT_SUITE, knight_movement_nearby)
{
    const sf::Vector2u &startPosition = {3, 3};
    bool expected = false;

    sf::Texture texture;
    sf::Vector2f size = {10, 10};

    auto knight = Knight(texture, size, Player::PLAYER_1);
    knight.SetToBox(startPosition);

    ASSERT_EQ(knight.CanMove({startPosition.x - 1, startPosition.y}), expected);
    ASSERT_EQ(knight.CanMove({startPosition.x + 1, startPosition.y}), expected);
    ASSERT_EQ(knight.CanMove({startPosition.x, startPosition.y - 1}), expected);
    ASSERT_EQ(knight.CanMove({startPosition.x, startPosition.y + 1}), expected);
}

TEST(KNIGHT_SUITE, knight_movement_nearby_diagonal)
{
    const sf::Vector2u &startPosition = {3, 3};
    bool expected = false;

    sf::Texture texture;
    sf::Vector2f size = {10, 10};

    auto knight = Knight(texture, size, Player::PLAYER_1);
    knight.SetToBox(startPosition);

    ASSERT_EQ(knight.CanMove({startPosition.x + 1, startPosition.y + 1}), expected);
    ASSERT_EQ(knight.CanMove({startPosition.x + 1, startPosition.y - 1}), expected);
    ASSERT_EQ(knight.CanMove({startPosition.x - 1, startPosition.y + 1}), expected);
    ASSERT_EQ(knight.CanMove({startPosition.x - 1, startPosition.y - 1}), expected);
}

TEST(KNIGHT_SUITE, knight_movement_two_and_half)
{
    const sf::Vector2u &startPosition = {3, 3};
    bool expected = true;

    sf::Texture texture;
    sf::Vector2f size = {10, 10};

    auto knight = Knight(texture, size, Player::PLAYER_1);
    knight.SetToBox(startPosition);

    ASSERT_EQ(knight.CanMove({startPosition.x + 2, startPosition.y + 1}), expected);
    ASSERT_EQ(knight.CanMove({startPosition.x - 2, startPosition.y + 1}), expected);
    ASSERT_EQ(knight.CanMove({startPosition.x + 2, startPosition.y - 1}), expected);
    ASSERT_EQ(knight.CanMove({startPosition.x - 2, startPosition.y - 1}), expected);
    ASSERT_EQ(knight.CanMove({startPosition.x + 1, startPosition.y + 2}), expected);
    ASSERT_EQ(knight.CanMove({startPosition.x - 1, startPosition.y + 2}), expected);
    ASSERT_EQ(knight.CanMove({startPosition.x + 1, startPosition.y - 2}), expected);
    ASSERT_EQ(knight.CanMove({startPosition.x - 1, startPosition.y - 2}), expected);
}
