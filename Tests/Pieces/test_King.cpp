#include <gtest/gtest.h>
#include "Pieces/King.h"

static void checkRange(King &king, const sf::Vector2u &startPosition, const sf::Vector2i &delta, bool expected, const sf::Vector2u *excludeList = nullptr, size_t excludeListSize = 0)
{
    king.SetToBox(startPosition);
    sf::Vector2u testPosition = startPosition;
    
    /* no delta, creates infinite loop */
    ASSERT_FALSE(delta.x == 0 && delta.y == 0);
    
    /* can not move to start position */
    ASSERT_EQ(king.CanMove(testPosition), false);

    do
    {
        testPosition.x = testPosition.x + delta.x;
        testPosition.y = testPosition.y + delta.y;
        bool skipCheck = false;

        for (size_t i = 0; i < excludeListSize; i++)
            skipCheck |= (excludeList && excludeList[i] == testPosition);

        if (!skipCheck)
            ASSERT_EQ(king.CanMove(testPosition), expected);
    } while (testPosition.x > 0 && testPosition.y > 0 && testPosition.x < 7 && testPosition.y < 7);
}

TEST(KING_SUITE, Initialization)
{
    sf::Texture texture;
    sf::Vector2f size = {10, 10};

    auto king = King(texture, size, Player::PLAYER_1);

    ASSERT_EQ(king.GetPlayer(), Player::PLAYER_1);
}

TEST(KING_SUITE, king_movement_vertical_up)
{
    const sf::Vector2u &startPosition = {0, 7};
    const sf::Vector2i &delta = {0, -1};
    bool expected = false;
    const sf::Vector2u excludeList[] =
        {
            /* exclude immediate above box */
            {startPosition.x + delta.x, startPosition.y + delta.y}};

    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto king = King(texture, size, Player::PLAYER_1);

    checkRange(
        king,
        startPosition,
        delta,
        expected,
        excludeList,
        sizeof(excludeList) / sizeof(excludeList));
}

TEST(KING_SUITE, king_movement_vertical_down)
{
    const sf::Vector2u &startPosition = {0, 0};
    const sf::Vector2i &delta = {0, 1};
    bool expected = false;
    const sf::Vector2u excludeList[] =
        {
            /* exclude immediate below box */
            {startPosition.x + delta.x, startPosition.y + delta.y}};

    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto king = King(texture, size, Player::PLAYER_1);

    checkRange(
        king,
        startPosition,
        delta,
        expected,
        excludeList,
        sizeof(excludeList) / sizeof(excludeList));
}

TEST(KING_SUITE, king_movement_horizontal_left)
{
    const sf::Vector2u &startPosition = {7, 0};
    const sf::Vector2i &delta = {-1, 0};
    bool expected = false;
    const sf::Vector2u excludeList[] =
        {
            {startPosition.x + delta.x, startPosition.y + delta.y}};
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto king = King(texture, size, Player::PLAYER_1);

    checkRange(
        king,
        startPosition,
        delta,
        expected,
        excludeList,
        sizeof(excludeList) / sizeof(excludeList));
}

TEST(KING_SUITE, king_movement_horizontal_right)
{
    const sf::Vector2u &startPosition = {0, 0};
    const sf::Vector2i &delta = {1, 0};
    bool expected = false;
    const sf::Vector2u excludeList[] =
        {
            {startPosition.x + delta.x, startPosition.y + delta.y}};
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto king = King(texture, size, Player::PLAYER_1);

    checkRange(
        king,
        startPosition,
        delta,
        expected,
        excludeList,
        sizeof(excludeList) / sizeof(excludeList));
}

TEST(KING_SUITE, king_movement_diagonal_bottom_right)
{
    const sf::Vector2u &startPosition = {0, 0};
    const sf::Vector2i &delta = {1, 1};
    bool expected = false;
    const sf::Vector2u excludeList[] =
        {
            {startPosition.x + delta.x, startPosition.y + delta.y}};
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto king = King(texture, size, Player::PLAYER_1);

    checkRange(
        king,
        startPosition,
        delta,
        expected,
        excludeList,
        sizeof(excludeList) / sizeof(excludeList));
}

TEST(KING_SUITE, king_movement_diagonal_bottom_left)
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
    auto king = King(texture, size, Player::PLAYER_1);

    checkRange(
        king,
        startPosition,
        delta,
        expected,
        excludeList,
        sizeof(excludeList) / sizeof(excludeList));
}

TEST(KING_SUITE, king_movement_diagonal_top_right)
{
    const sf::Vector2u &startPosition = {0, 7};
    const sf::Vector2i &delta = {1, -1};
    bool expected = false;
    const sf::Vector2u excludeList[] =
        {
            {startPosition.x + delta.x, startPosition.y + delta.y}};
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto king = King(texture, size, Player::PLAYER_1);

    checkRange(
        king,
        startPosition,
        delta,
        expected,
        excludeList,
        sizeof(excludeList) / sizeof(excludeList));
}

TEST(KING_SUITE, king_movement_diagonal_top_left)
{
    const sf::Vector2u &startPosition = {7, 7};
    const sf::Vector2i &delta = {-1, -1};
    bool expected = false;
    const sf::Vector2u excludeList[] =
        {
            {startPosition.x + delta.x, startPosition.y + delta.y}};
    sf::Texture texture;
    sf::Vector2f size = {10, 10};
    auto king = King(texture, size, Player::PLAYER_1);

    checkRange(
        king,
        startPosition,
        delta,
        expected,
        excludeList,
        sizeof(excludeList) / sizeof(excludeList));
}

TEST(KING_SUITE, king_movement_nearby)
{
    const sf::Vector2u &startPosition = {3, 3};
    bool expected = true;

    sf::Texture texture;
    sf::Vector2f size = {10, 10};

    auto king = King(texture, size, Player::PLAYER_1);
    king.SetToBox(startPosition);

    ASSERT_EQ(king.CanMove({startPosition.x - 1, startPosition.y}), expected);
    ASSERT_EQ(king.CanMove({startPosition.x + 1, startPosition.y}), expected);
    ASSERT_EQ(king.CanMove({startPosition.x, startPosition.y - 1}), expected);
    ASSERT_EQ(king.CanMove({startPosition.x, startPosition.y + 1}), expected);
}

TEST(KING_SUITE, king_movement_nearby_diagonal)
{
    const sf::Vector2u &startPosition = {3, 3};
    bool expected = true;

    sf::Texture texture;
    sf::Vector2f size = {10, 10};

    auto king = King(texture, size, Player::PLAYER_1);
    king.SetToBox(startPosition);

    ASSERT_EQ(king.CanMove({startPosition.x + 1, startPosition.y + 1}), expected);
    ASSERT_EQ(king.CanMove({startPosition.x + 1, startPosition.y - 1}), expected);
    ASSERT_EQ(king.CanMove({startPosition.x - 1, startPosition.y + 1}), expected);
    ASSERT_EQ(king.CanMove({startPosition.x - 1, startPosition.y - 1}), expected);
}

TEST(KING_SUITE, king_movement_two_and_half)
{
    const sf::Vector2u &startPosition = {3, 3};
    bool expected = false;

    sf::Texture texture;
    sf::Vector2f size = {10, 10};

    auto king = King(texture, size, Player::PLAYER_1);
    king.SetToBox(startPosition);

    ASSERT_EQ(king.CanMove({startPosition.x + 2, startPosition.y + 1}), expected);
    ASSERT_EQ(king.CanMove({startPosition.x - 2, startPosition.y + 1}), expected);
    ASSERT_EQ(king.CanMove({startPosition.x + 2, startPosition.y - 1}), expected);
    ASSERT_EQ(king.CanMove({startPosition.x - 2, startPosition.y - 1}), expected);
    ASSERT_EQ(king.CanMove({startPosition.x + 1, startPosition.y + 2}), expected);
    ASSERT_EQ(king.CanMove({startPosition.x - 1, startPosition.y + 2}), expected);
    ASSERT_EQ(king.CanMove({startPosition.x + 1, startPosition.y - 2}), expected);
    ASSERT_EQ(king.CanMove({startPosition.x - 1, startPosition.y - 2}), expected);
}
