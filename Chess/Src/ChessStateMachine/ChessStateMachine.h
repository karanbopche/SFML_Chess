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
    Piece *captured[4][8];
    sf::Sprite boardSprites[10][10];
    const unsigned int VERTICAL_BOXES = 8;
    const unsigned int HORIZONTAL_BOXES = 8;
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
