#include "IdleState.h"

void IdleState::EnterState()
{
}

void IdleState::Draw()
{
}

void IdleState::EventHandler(sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonReleased)
    {
        const auto mousePosition = sf::Mouse::getPosition(*this->context.window);
        const auto boxSize = this->context.window->getSize() / this->context.VERTICAL_BOXES;
        sf::Vector2u selectedBox = {mousePosition.x / boxSize.x, mousePosition.y / boxSize.y};
        if(this->IsValidSelection(selectedBox))
        {
            this->context.selectedPiecePosition = selectedBox;
            this->SetNextState(ChessStateKeys::PieceSelectedStateKey);
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
    if(piece == nullptr)
        return false;
    
    /* wrong player */
    if(this->context.currentPlayer != piece->GetPlayer())
        return false;

    return true;
}