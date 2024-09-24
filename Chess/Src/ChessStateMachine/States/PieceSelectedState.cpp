#include "PieceSelectedState.h"

PieceSelectedState::PieceSelectedState(ChessContext &context) : ChessState(context, ChessStateKeys::PieceSelectedStateKey)
{
}

void PieceSelectedState::EnterState()
{
    this->HighlightPossibleMove(this->context.pieces[this->context.selectedPiecePosition.y][this->context.selectedPiecePosition.x]);
    this->context.boardSprites[this->context.selectedPiecePosition.y][this->context.selectedPiecePosition.x].setColor(sf::Color::Green);
}

void PieceSelectedState::ExitState()
{
    for (unsigned int row = 0; row < this->context.ROWS; row++)
        for (unsigned int col = 0; col < this->context.COLS; col++)
            this->context.boardSprites[row][col].setColor(sf::Color::White);
}

void PieceSelectedState::EventHandler(sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonReleased)
    {
        if(this->context.boardRect.contains(event.mouseButton.x, event.mouseButton.y))
        {
            sf::Vector2u selectedBox = {
                static_cast<unsigned int>((event.mouseButton.x - this->context.boardRect.left) / this->context.BoxSize.x),
                static_cast<unsigned int>((event.mouseButton.y - this->context.boardRect.top) / this->context.BoxSize.y)};
            if (this->IsValidMove(this->context.selectedPiecePosition, selectedBox, this->context.currentPlayer))
            {
                this->MovePiece(this->context.selectedPiecePosition, selectedBox);
                this->context.targetPiecePosition = selectedBox;
                this->SetNextState(ChessStateKeys::CheckStateKey);
            }
            else
                this->SetNextState(ChessStateKeys::IdleStateKey);
        }
    }
}

void PieceSelectedState::Update()
{
}

void PieceSelectedState::Draw()
{
}

void PieceSelectedState::MovePiece(const sf::Vector2u &from, const sf::Vector2u &to)
{
    /* kill piece */
    if (this->context.pieces[to.y][to.x])
    {
        this->CapturePiece(to);
    }

    this->context.pieces[from.y][from.x]->MoveToBox(to);
    std::swap(this->context.pieces[from.y][from.x], this->context.pieces[to.y][to.x]);
}

void PieceSelectedState::CapturePiece(const sf::Vector2u &piecePosition)
{
    auto capturedPlayer = this->context.pieces[piecePosition.y][piecePosition.x]->GetPlayer();
    unsigned int index = 0;
    auto &capturePieces = (capturedPlayer == Player::PLAYER_1) ? this->context.player1CapturedPieces : this->context.player2CapturedPieces;
    auto offset = (capturedPlayer == Player::PLAYER_1) ? sf::Vector2f(0, 0) : sf::Vector2f(this->context.BoxSize.x * 10 + 80.f, 0.f);
    for (unsigned int x = 0; x < 2; x++)
        for (unsigned int y = 0; y < 8; y++)
        {
            if (capturePieces[y][x] == nullptr)
            {
                capturePieces[y][x] = this->context.pieces[piecePosition.y][piecePosition.x];
                capturePieces[y][x]->SetOffset(offset);
                capturePieces[y][x]->SetToBox({x, y});
                break;
            }
        }
    this->context.pieces[piecePosition.y][piecePosition.x] = nullptr;
}

void PieceSelectedState::HighlightPossibleMove(Piece *piece)
{
    for (unsigned int row = 0; row < this->context.ROWS; row++)
        for (unsigned int col = 0; col < this->context.COLS; col++)
        {
            sf::Color color;
            if (this->IsValidMove(piece->GetBoxPosition(), {col, row}, piece->GetPlayer()))
                this->context.boardSprites[row][col].setColor(this->context.hintBoxColor);
            else
                this->context.boardSprites[row][col].setColor(this->context.noColor);
        }
}
