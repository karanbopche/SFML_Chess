#pragma once

#include <SFML/Graphics.hpp>

enum class Player
{
    PLAYER_1,
    PLAYER_2
};

enum class PieceType
{
    Bishop,
    King,
    Knight,
    Pawn,
    Queen,
    Rook
};

class Piece
{
public:
    explicit Piece(const sf::Texture &texture, const sf::Vector2f &size, const Player player, const PieceType type);
    virtual ~Piece() = default;
    virtual bool CanMove(const sf::Vector2u &position) = 0;

    sf::Vector2u GetBoxPosition() const;
    void Update();

    inline PieceType GetPieceType() 
    {
        return this->type;
    }
    inline void SetOffset(const sf::Vector2f &offset)
    {
        this->offset = offset;
    }
    inline void SetPosition(const sf::Vector2f &position)
    {
        this->targetPosition = position;
    }
    inline void MoveToBox(const sf::Vector2u &boxPosition)
    {
        this->targetPosition = {this->offset.x + (boxPosition.x * this->size.x), this->offset.y + (boxPosition.y * this->size.y)};
    }
    inline void SetToBox(sf::Vector2u box)
    {
        this->targetPosition = {this->offset.x + (box.x * this->size.x), this->offset.y + (box.y * size.y)};
        this->sprite.setPosition(this->targetPosition);
    }
    inline void Draw(sf::RenderWindow *window) const
    {
        window->draw(this->sprite);
    }
    inline sf::Vector2f GetPosition() const
    {
        return this->sprite.getPosition();
    }
    inline Player GetPlayer() const
    {
        return this->player;
    }
    inline bool IsMoving() const
    {
        return !AlmostEqual(this->GetPosition(), this->targetPosition);
    }

protected:
    inline bool AlmostEqual(const sf::Vector2f &a, const sf::Vector2f &b) const
    {
        return (std::abs(a.x - b.y) <= this->deltaStep) && (std::abs(a.y - b.y) <= this->deltaStep);
    }
    sf::Vector2f LinearInterpolate(const sf::Vector2f &from, const sf::Vector2f &to) const;

    sf::Sprite sprite;
    sf::Vector2f targetPosition;
    float interpolateStep;
    float deltaStep;
    const sf::Vector2f size;
    const Player player;
    const PieceType type;
    sf::Vector2f offset;
};

