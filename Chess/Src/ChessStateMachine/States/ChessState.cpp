#include "ChessState.h"


bool ChessState::IsValidMove(const sf::Vector2u& from, const sf::Vector2u& to, Player player)
{
    auto &playerPiece = this->context.pieces[from.y][from.x];
    auto &opponentPiece = this->context.pieces[to.y][to.x];

    /* piece can't move to location */
    if (playerPiece->CanMove(to) == false)
        return false;

    /* knight can jump over other pieces */
    if (playerPiece->GetPieceType() != PieceType::Knight)
    {
        if (this->isPathBlocked(from, to))
            return false;
    }
    /* trying to attack other piece */
    if ((opponentPiece != nullptr))
    {
        /* trying to attack same player */
        if (opponentPiece->GetPlayer() == player)
            return false;

        /* special case for pawn */
        if (playerPiece->GetPieceType() == PieceType::Pawn)
        {
            /* pawn only attack diagonally */
            if (from.x == to.x)
                return false;
        }
    }
    else
    {
        /* pawn can not move diagonally if not attacking */
        if (playerPiece->GetPieceType() == PieceType::Pawn && from.x != to.x)
            return false;
    }
    /* if move cause check to own king */
    auto const king = this->FindKing(playerPiece->GetPlayer());
    if(this->GetAttackers(king->GetPlayer(), king->GetBoxPosition()).size() != 0)
        return false;
    
    return true;
}

bool ChessState::isPathBlocked(sf::Vector2u from, sf::Vector2u to)
{
    sf::Vector2i delta = {
        static_cast<int>(to.x) - static_cast<int>(from.x),
        static_cast<int>(to.y) - static_cast<int>(from.y)};
    /* only sign of delta needed */
    delta.x = (0 < delta.x) - (delta.x < 0);
    delta.y = (0 < delta.y) - (delta.y < 0);
    /* skip last */
    to.x = to.x - delta.x;
    to.y = to.y - delta.y;

    while ((to.x != from.x) || (to.y != from.y))
    {
        if(from.x != to.x)
            from.x = from.x + delta.x;
        if(from.y != to.y)
            from.y = from.y + delta.y;
        /* blocked by another piece */
        if (this->context.pieces[from.y][from.x] != nullptr)
            return true;
    }
    return false;
}

Piece *ChessState::FindKing(Player player)
{
    for (unsigned int y = 0; y < this->context.ROWS; y++)
        for (unsigned int x = 0; x < this->context.COLS; x++)
        {
            auto &piece = this->context.pieces[y][x];
            if (piece && piece->GetPieceType() == PieceType::King && piece->GetPlayer() == player)
                return piece;
        }
    return nullptr;
}

std::vector<Piece *> ChessState::GetAttackers(Player attacker, const sf::Vector2u &position)
{
    std::vector<Piece *> attackers;
    for (unsigned int y = 0; y < this->context.ROWS; y++)
        for (unsigned int x = 0; x < this->context.COLS; x++)
        {
            auto &piece = this->context.pieces[y][x];
            if (piece && piece->GetPlayer() == attacker && this->IsValidMove(piece->GetBoxPosition(), position, attacker))
                attackers.push_back(piece);
        }
    return attackers;
}
