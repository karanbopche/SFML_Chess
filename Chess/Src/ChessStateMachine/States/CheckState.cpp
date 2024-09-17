#include "CheckState.h"

void CheckState::EnterState()
{
    auto opponentPlayer = (this->context.currentPlayer == Player::PLAYER_1) ? Player::PLAYER_2 : Player::PLAYER_1;
    auto opponentKing = this->FindKing(opponentPlayer);
    auto opponentKingPos = opponentKing->GetBoxPosition();
    auto attackers = this->GetAttackers(this->context.currentPlayer, opponentKingPos);

    this->SetNextState(ChessStateKeys::IdleStateKey);
    /* no check */
    if (attackers.size() == 0)
        return;
    /* highlight attackers and king */
    for (auto &attacker : attackers)
    {
        const auto &pos = attacker->GetBoxPosition();
        this->context.boardSprites[pos.y][pos.x].setColor(this->context.attackerBoxColor);
    }
    this->context.boardSprites[opponentKingPos.y][opponentKingPos.x].setColor(this->context.checkBoxColor);
    /* is checkmate */
    /* can avoid check by moving king */
    if (this->CanAvoidAttackByMoving(opponentKing))
        return;

    /* can avoid check by blocking path if checked by single piece */
    if (attackers.size() == 1 && this->CanBlockPath(opponentKingPos, attackers[0]->GetBoxPosition(), this->context.currentPlayer))
        return;

    this->SetNextState(ChessStateKeys::CheckMateStateKey);

}

void CheckState::ExitState()
{
    this->SwitchPlayer();
}

void CheckState::EventHandler(sf::Event &event)
{
}

void CheckState::Update()
{
}

void CheckState::Draw()
{
}

bool CheckState::CanAvoidAttackByMoving(Piece *piece)
{
    const auto &pos = piece->GetBoxPosition();
    auto player = piece->GetPlayer();
    for (unsigned int y = 0; y < this->context.VERTICAL_BOXES; y++)
        for (unsigned int x = 0; x < this->context.HORIZONTAL_BOXES; x++)
            if (this->IsValidMove(pos, {x, y}, player))
                return true;

    return false;
}

bool CheckState::CanBlockPath(sf::Vector2u from, sf::Vector2u to, Player player)
{
    sf::Vector2i delta = {
        static_cast<int>(to.x) - static_cast<int>(from.x),
        static_cast<int>(to.y) - static_cast<int>(from.y)};
    /* only sign of delta needed */
    delta.x = (0 < delta.x) - (delta.x < 0);
    delta.y = (0 < delta.y) - (delta.y < 0);

    for (unsigned int y = 0; y < this->context.VERTICAL_BOXES; y++)
        for (unsigned int x = 0; x < this->context.HORIZONTAL_BOXES; x++)
            if (this->context.pieces[y][x])
                while ((to.x != from.x) || (to.y != from.y))
                {
                    if (from.x != to.x)
                        from.x = from.x + delta.x;
                    if (from.y != to.y)
                        from.y = from.y + delta.y;
                    /* can block check by another player */
                    if (this->IsValidMove({x, y}, from, player))
                        return true;
                }
    return false;
}
