#pragma once
#include <Pieces/Piece.h>
#include <StateMachine/HierarchicalStateMachine.h>

struct ChessContext
{
    sf::RenderWindow* window;
    sf::Vector2u selectedPiecePosition;
    sf::Vector2u targetPiecePosition;
    Player currentPlayer;
    Piece *pieces[8][8];
    sf::Sprite boardSprites[8][8];
    Piece *player1CapturedPieces[8][2];
    Piece *player2CapturedPieces[8][2];
    sf::Sprite player1CaptureSprites[8][2];
    sf::Sprite player2CaptureSprites[8][2];
    sf::Vector2f BoxSize;
    sf::FloatRect boardRect;
    const unsigned int ROWS = 8;
    const unsigned int COLS = 8;
    const sf::Color selectedPieceBoxColor = sf::Color::Green;
    const sf::Color hintBoxColor = sf::Color::Cyan;
    const sf::Color checkBoxColor = sf::Color::Red;
    const sf::Color attackerBoxColor = sf::Color::Magenta;
    const sf::Color noColor = sf::Color::White;
};

enum ChessStateKeys
{
    IdleStateKey,
    PieceSelectedStateKey,
    CheckStateKey,
    CheckMateStateKey,
};

class ChessStateMachine: public HierarchicalStateMachine<ChessStateKeys, ChessContext>
{
public:

    ChessStateMachine(sf::RenderWindow* window);
    void Update() override;
    void Draw() override;

protected:
    void InitStates();
    void InitPlayer();
    void InitBoard();
};
