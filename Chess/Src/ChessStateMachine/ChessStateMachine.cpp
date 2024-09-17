#include <Pieces/Pawn.h>
#include <Pieces/Bishop.h>
#include <Pieces/Knight.h>
#include <Pieces/King.h>
#include <Pieces/Queen.h>
#include <Pieces/Rook.h>
#include <Manager/TextureManager.h>

#include "ChessStateMachine.h"
#include "States/IdleState.h"
#include "States/PieceSelectedState.h"
#include "States/CheckState.h"
#include "States/CheckMateState.h"

ChessStateMachine::ChessStateMachine(sf::RenderWindow* window)
{
    this->context.window = window;
    this->context.currentPlayer = Player::PLAYER_1;
    this->InitStates();
    this->InitBoard();
    this->InitPlayer();
}

void ChessStateMachine::InitStates()
{
    this->RegisterState(ChessStateKeys::IdleStateKey, std::move(std::make_unique<IdleState>(this->context)));
    this->RegisterState(ChessStateKeys::PieceSelectedStateKey, std::move(std::make_unique<PieceSelectedState>(this->context)));
    this->RegisterState(ChessStateKeys::CheckStateKey, std::move(std::make_unique<CheckState>(this->context)));
    this->RegisterState(ChessStateKeys::CheckMateStateKey, std::move(std::make_unique<CheckMateState>(this->context)));
    
    this->currentState = ChessStateKeys::IdleStateKey;
}

void ChessStateMachine::InitBoard()
{
    auto textureManager = TextureManager::GetInstance();

    const auto &boardBlackTexture = textureManager->GetItem("board-black");
    const auto &boardWhiteTexture = textureManager->GetItem("board-white");
    auto boxSize = this->context.window->getSize() / this->context.VERTICAL_BOXES;
    const auto BoxTextureSize = boardWhiteTexture.getSize();

    sf::Vector2f boxScale = {(float)boxSize.x / BoxTextureSize.x, (float)boxSize.y / BoxTextureSize.y};
    for (unsigned int y = 0; y < this->context.VERTICAL_BOXES; y++)
    {
        int idx = y % 2;
        for (unsigned int x = 0; x < this->context.HORIZONTAL_BOXES; x++)
        {
            this->context.pieces[y][x] = nullptr;
            this->context.boardSprites[y][x].setPosition({(float)x * boxSize.x, (float)y * boxSize.y});
            this->context.boardSprites[y][x].setScale(boxScale);
            if (idx % 2)
                this->context.boardSprites[y][x].setTexture(boardBlackTexture);
            else
                this->context.boardSprites[y][x].setTexture(boardWhiteTexture);
            idx++;
        }
    }
}

void ChessStateMachine::InitPlayer()
{
    auto textureManager = TextureManager::GetInstance();
    auto windowSize = this->context.window->getSize();
    sf::Vector2f boxSize = {(float)windowSize.x / this->context.HORIZONTAL_BOXES, (float)windowSize.y / this->context.VERTICAL_BOXES};
    const auto &pawn_white = textureManager->GetItem("pawn_white");
    const auto &pawn_black = textureManager->GetItem("pawn_black");

    for (unsigned int i = 0; i < 8; i++)
    {
        this->context.pieces[1][i] = new Pawn(pawn_white, boxSize, Player::PLAYER_2);
        this->context.pieces[1][i]->SetToBox({i, 1});
        this->context.pieces[6][i] = new Pawn(pawn_black, boxSize, Player::PLAYER_1);
        this->context.pieces[6][i]->SetToBox({i, 6});
    }

    this->context.pieces[0][3] = new King(textureManager->GetItem("king_white"), boxSize, Player::PLAYER_2);
    this->context.pieces[0][3]->SetToBox({3, 0});
    this->context.pieces[7][3] = new King(textureManager->GetItem("king_black"), boxSize, Player::PLAYER_1);
    this->context.pieces[7][3]->SetToBox({3, 7});

    this->context.pieces[0][4] = new Rook(textureManager->GetItem("queen_white"), boxSize, Player::PLAYER_2);
    this->context.pieces[0][4]->SetToBox({4, 0});
    this->context.pieces[7][4] = new Rook(textureManager->GetItem("queen_black"), boxSize, Player::PLAYER_1);
    this->context.pieces[7][4]->SetToBox({4, 7});

    this->context.pieces[0][0] = new Rook(textureManager->GetItem("rook_white"), boxSize, Player::PLAYER_2);
    this->context.pieces[0][0]->SetToBox({0, 0});
    this->context.pieces[7][0] = new Rook(textureManager->GetItem("rook_black"), boxSize, Player::PLAYER_1);
    this->context.pieces[7][0]->SetToBox({0, 7});
    this->context.pieces[0][7] = new Rook(textureManager->GetItem("rook_white"), boxSize, Player::PLAYER_2);
    this->context.pieces[0][7]->SetToBox({7, 0});
    this->context.pieces[7][7] = new Rook(textureManager->GetItem("rook_black"), boxSize, Player::PLAYER_1);
    this->context.pieces[7][7]->SetToBox({7, 7});

    this->context.pieces[0][1] = new Knight(textureManager->GetItem("knight_white"), boxSize, Player::PLAYER_2);
    this->context.pieces[0][1]->SetToBox({1, 0});
    this->context.pieces[7][1] = new Knight(textureManager->GetItem("knight_black"), boxSize, Player::PLAYER_1);
    this->context.pieces[7][1]->SetToBox({1, 7});
    this->context.pieces[0][6] = new Knight(textureManager->GetItem("knight_white"), boxSize, Player::PLAYER_2);
    this->context.pieces[0][6]->SetToBox({6, 0});
    this->context.pieces[7][6] = new Knight(textureManager->GetItem("knight_black"), boxSize, Player::PLAYER_1);
    this->context.pieces[7][6]->SetToBox({6, 7});

    this->context.pieces[0][2] = new Bishop(textureManager->GetItem("bishop_white"), boxSize, Player::PLAYER_2);
    this->context.pieces[0][2]->SetToBox({2, 0});
    this->context.pieces[7][2] = new Bishop(textureManager->GetItem("bishop_black"), boxSize, Player::PLAYER_1);
    this->context.pieces[7][2]->SetToBox({2, 7});
    this->context.pieces[0][5] = new Bishop(textureManager->GetItem("bishop_white"), boxSize, Player::PLAYER_2);
    this->context.pieces[0][5]->SetToBox({5, 0});
    this->context.pieces[7][5] = new Bishop(textureManager->GetItem("bishop_black"), boxSize, Player::PLAYER_1);
    this->context.pieces[7][5]->SetToBox({5, 7});
}

void ChessStateMachine::Update()
{
    for (auto &row : this->context.pieces)
        for (auto &piece : row)
            if (piece)
                piece->Update();
    
    HierarchicalStateMachine::Update();
}

void ChessStateMachine::Draw()
{
    for (const auto &row : this->context.boardSprites)
        for (const auto &block : row)
            this->context.window->draw(block);

    for (const auto &row : this->context.pieces)
        for (const auto &piece : row)
            if (piece)
                piece->Draw(this->context.window);
    HierarchicalStateMachine::Draw();
}