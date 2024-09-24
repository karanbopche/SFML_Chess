#include "IdleState.h"

void IdleState::EnterState()
{
}

void IdleState::Draw()
{
}

void IdleState::EventHandler(sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonReleased)
    {
        if(this->context.boardRect.contains(event.mouseButton.x, event.mouseButton.y))
        {
            sf::Vector2u selectedBox = {
                static_cast<unsigned int>((event.mouseButton.x - this->context.boardRect.left) / this->context.BoxSize.x),
                static_cast<unsigned int>((event.mouseButton.y - this->context.boardRect.top) / this->context.BoxSize.y)};
            if (this->IsValidSelection(selectedBox))
            {
                this->context.selectedPiecePosition = selectedBox;
                this->SetNextState(ChessStateKeys::PieceSelectedStateKey);
            }
        }
    }
}

void IdleState::Update()
{
}

void IdleState::ExitState()
{
}

bool IdleState::IsValidSelection(const sf::Vector2u &position)
{
    auto &piece = this->context.pieces[position.y][position.x];

    /* no piece selected */
    if (piece == nullptr)
        return false;

    /* wrong player */
    if (this->context.currentPlayer != piece->GetPlayer())
        return false;

    return true;
}