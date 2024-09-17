#include "Bishop.h"
#include "Config.h"
#include "Manager/TextureManager.h"


Bishop::Bishop(const sf::Texture& texture, const sf::Vector2f& size, Player player) : Piece(texture, size, player, PieceType::Bishop)
{
}

bool Bishop::CanMove(const sf::Vector2u& position)
{
    const auto currentPosition = this->GetBoxPosition();
    const sf::Vector2i delta = {
        std::abs(static_cast<int>(position.x) - static_cast<int>(currentPosition.x)),
        std::abs(static_cast<int>(position.y) - static_cast<int>(currentPosition.y))
    };
    if (currentPosition == position)
        return false;
    if(delta.x == delta.y)
        return true;
    return false;
}