#include "Queen.h"
#include "Config.h"
#include "Manager/TextureManager.h"


Queen::Queen(const sf::Texture& texture, const sf::Vector2f& size, Player player) : Piece(texture, size, player, PieceType::Queen)
{
}

bool Queen::CanMove(const sf::Vector2u& position)
{
    auto currentPosition = this->GetBoxPosition();
    sf::Vector2i delta = {
        std::abs(static_cast<int>(currentPosition.x) - static_cast<int>(position.x)),
        std::abs(static_cast<int>(currentPosition.y) - static_cast<int>(position.y))
    };
    if (currentPosition == position)
        return false;
    // adjecent boxes.
    if(delta.x < 2 && delta.y < 2)
        return true;
    // vertical and horizontal.
    if((delta.x != 0) ^ (delta.y != 0))
        return true;
    // diagonals.
    if(delta.x == delta.y)
        return true;
    return false;
}
