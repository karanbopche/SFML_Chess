#include "King.h"
#include "Config.h"
#include "Manager/TextureManager.h"

King::King(const sf::Texture &texture, const sf::Vector2f &size, Player player) : Piece(texture, size, player, PieceType::King)
{
}

bool King::CanMove(const sf::Vector2u &position)
{
    auto currentPosition = this->GetBoxPosition();
    sf::Vector2i delta = {
        std::abs(static_cast<int>(currentPosition.x) - static_cast<int>(position.x)),
        std::abs(static_cast<int>(currentPosition.y) - static_cast<int>(position.y))};
    if (currentPosition == position)
        return false;
    if (delta.x < 2 && delta.y < 2)
        return true;
    return false;
}