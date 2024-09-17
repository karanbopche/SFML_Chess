#include "Pawn.h"
#include "Config.h"
#include "Manager/TextureManager.h"


Pawn::Pawn(const sf::Texture& texture, const sf::Vector2f& size, Player player) : Piece(texture, size, player, PieceType::Pawn)
{
}

bool Pawn::CanMove(const sf::Vector2u& position)
{
    auto currentPosition = this->GetBoxPosition();
    sf::Vector2i delta = {
        static_cast<int>(position.x) - static_cast<int>(currentPosition.x),
        static_cast<int>(position.y) - static_cast<int>(currentPosition.y)
    };
    if (currentPosition == position)
        return false;
    if((std::abs(delta.y) < 3) && (std::abs(delta.x) < 2) && (delta.y != 0))
    {
        if(this->player == Player::PLAYER_1)
            return (delta.y == -1) || (currentPosition.y == 6 && delta.x == 0 && delta.y == -2);
        else
            return (delta.y == 1) || (currentPosition.y == 1 && delta.x == 0 && delta.y == 2);
    }
    return false;
}
