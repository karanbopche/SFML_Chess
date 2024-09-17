#include "PieceSelectedState.h"


PieceSelectedState::PieceSelectedState(ChessContext &context): ChessState(context, ChessStateKeys::PieceSelectedStateKey)
{
}

void PieceSelectedState::EnterState()
{
    this->HighlightPossibleMove(this->context.pieces[this->context.selectedPiecePosition.y][this->context.selectedPiecePosition.x]);
    this->context.boardSprites[this->context.selectedPiecePosition.y][this->context.selectedPiecePosition.x].setColor(sf::Color::Green);
}

void PieceSelectedState::ExitState()
{
    for(unsigned int row=0;row<this->context.VERTICAL_BOXES;row++)
        for(unsigned int col=0;col<this->context.HORIZONTAL_BOXES;col++)
            this->context.boardSprites[row][col].setColor(sf::Color::White);
}

void PieceSelectedState::EventHandler(sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonReleased)
    {
        const auto mousePosition = sf::Mouse::getPosition(*this->context.window);
        const auto boxSize = this->context.window->getSize() / this->context.VERTICAL_BOXES;
        sf::Vector2u selectedBox = {mousePosition.x / boxSize.x, mousePosition.y / boxSize.y};
        
        if(this->IsValidMove(this->context.selectedPiecePosition, selectedBox, this->context.currentPlayer))
        {
            this->MovePiece(this->context.selectedPiecePosition, selectedBox);
            this->context.targetPiecePosition = selectedBox;
            this->SetNextState(ChessStateKeys::CheckStateKey);
        }
        else
            this->SetNextState(ChessStateKeys::IdleStateKey);
    }
}

void PieceSelectedState::Update()
{
}

void PieceSelectedState::Draw()
{
}

void PieceSelectedState::MovePiece(const sf::Vector2u& from, const sf::Vector2u& to)
{
    /* kill piece */
    if(this->context.pieces[to.y][to.x])
    {
        this->CapturePiece(to);
    }

    this->context.pieces[from.y][from.x]->MoveToBox(to);
    std::swap(this->context.pieces[from.y][from.x], this->context.pieces[to.y][to.x]);
}

void PieceSelectedState::CapturePiece(const sf::Vector2u &piecePosition)
{
    delete this->context.pieces[piecePosition.y][piecePosition.x];
    this->context.pieces[piecePosition.y][piecePosition.x] = nullptr;
}

void PieceSelectedState::HighlightPossibleMove(Piece* piece)
{
    for(unsigned int row=0;row<this->context.VERTICAL_BOXES;row++)
        for(unsigned int col=0;col<this->context.HORIZONTAL_BOXES;col++)
        {
            sf::Color color;
            if(this->IsValidMove(piece->GetBoxPosition(), {col, row}, piece->GetPlayer()))
                this->context.boardSprites[row][col].setColor(this->context.hintBoxColor);
            else
                this->context.boardSprites[row][col].setColor(this->context.noColor);
        }
}
