#include "Piece.h"
#include "Config.h"


Piece::Piece(const sf::Texture& texture, const sf::Vector2f& size, Player player, const PieceType type) : size(size), player(player), type(type)
{
    this->sprite.setTexture(texture);
    auto tx_size = texture.getSize();
    this->sprite.setScale(size.x/tx_size.x, size.y/tx_size.y);
    this->interpolateStep = Config::GetInstance()->GetConfigFloat("piece", "interpolate_step");
    this->deltaStep = Config::GetInstance()->GetConfigFloat("piece", "delta_step");
}

sf::Vector2u Piece::GetBoxPosition() const
{
    const unsigned int x = (this->targetPosition.x + this->deltaStep - this->offset.x)  / this->size.x;
    const unsigned int y = (this->targetPosition.y + this->deltaStep - this->offset.y)  / this->size.y;
    return {x, y};
}

void Piece::Update()
{
    auto newPosition = this->LinearInterpolate(this->sprite.getPosition(), this->targetPosition);
    this->sprite.setPosition(newPosition);
}

sf::Vector2f Piece::LinearInterpolate(const sf::Vector2f& from, const sf::Vector2f& to) const
{
    if(this->AlmostEqual(from, to))
        return to;
    return from + this->interpolateStep * (to - from);
}
