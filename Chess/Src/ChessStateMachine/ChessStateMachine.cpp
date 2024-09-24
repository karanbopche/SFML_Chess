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

ChessStateMachine::ChessStateMachine(sf::RenderWindow *window)
{
    this->context.window = window;
    this->context.currentPlayer = Player::PLAYER_1;
    this->context.BoxSize = {100, 100};
    this->context.boardRect = sf::FloatRect(
        240,
        0,
        this->context.BoxSize.x * this->context.COLS,
        this->context.BoxSize.y * this->context.ROWS);
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
    const auto &boxSize = this->context.BoxSize;
    const auto BoxTextureSize = boardWhiteTexture.getSize();

    sf::Vector2f boxScale = {(float)boxSize.x / BoxTextureSize.x, (float)boxSize.y / BoxTextureSize.y};
    for (unsigned int y = 0; y < 8; y++)
        for (unsigned int x = 0; x < 2; x++)
        {
            this->context.player1CapturedPieces[y][x] = nullptr;
            this->context.player1CaptureSprites[y][x].setTexture(boardBlackTexture);
            this->context.player1CaptureSprites[y][x].setPosition({(float)x * boxSize.x, (float)y * boxSize.y});
            this->context.player1CaptureSprites[y][x].setScale(boxScale);
            this->context.player2CapturedPieces[y][x] = nullptr;
            this->context.player2CaptureSprites[y][x].setTexture(boardWhiteTexture);
            this->context.player2CaptureSprites[y][x].setPosition({(float)x * boxSize.x, (float)y * boxSize.y});
            this->context.player2CaptureSprites[y][x].setScale(boxScale);
            this->context.player2CaptureSprites[y][x].move({boxSize.x * 10 + 80.f, 0.f});
        }
    for (unsigned int y = 0; y < this->context.ROWS; y++)
    {
        int idx = y % 2;
        for (unsigned int x = 0; x < this->context.COLS; x++)
        {
            this->context.pieces[y][x] = nullptr;
            this->context.boardSprites[y][x].setPosition({(float)x * boxSize.x, (float)y * boxSize.y});
            this->context.boardSprites[y][x].setScale(boxScale);
            this->context.boardSprites[y][x].move({boxSize.x * 2 + 40.f, 0.f});
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
    const auto &boxSize = this->context.BoxSize;
    const auto &pawn_white = textureManager->GetItem("pawn_white");
    const auto &pawn_black = textureManager->GetItem("pawn_black");

    for (unsigned int i = 0; i < 8; i++)
    {
        this->context.pieces[1][i] = new Pawn(pawn_white, boxSize, Player::PLAYER_2);
        this->context.pieces[1][i]->SetOffset({240, 0});
        this->context.pieces[1][i]->SetToBox({i, 1});
        this->context.pieces[6][i] = new Pawn(pawn_black, boxSize, Player::PLAYER_1);
        this->context.pieces[6][i]->SetOffset({240, 0});
        this->context.pieces[6][i]->SetToBox({i, 6});
    }

    this->context.pieces[0][3] = new King(textureManager->GetItem("king_white"), boxSize, Player::PLAYER_2);
    this->context.pieces[0][3]->SetOffset({240, 0});
    this->context.pieces[0][3]->SetToBox({3, 0});
    this->context.pieces[7][3] = new King(textureManager->GetItem("king_black"), boxSize, Player::PLAYER_1);
    this->context.pieces[7][3]->SetOffset({240, 0});
    this->context.pieces[7][3]->SetToBox({3, 7});

    this->context.pieces[0][4] = new Rook(textureManager->GetItem("queen_white"), boxSize, Player::PLAYER_2);
    this->context.pieces[0][4]->SetOffset({240, 0});
    this->context.pieces[0][4]->SetToBox({4, 0});
    this->context.pieces[7][4] = new Rook(textureManager->GetItem("queen_black"), boxSize, Player::PLAYER_1);
    this->context.pieces[7][4]->SetOffset({240, 0});
    this->context.pieces[7][4]->SetToBox({4, 7});

    this->context.pieces[0][0] = new Rook(textureManager->GetItem("rook_white"), boxSize, Player::PLAYER_2);
    this->context.pieces[0][0]->SetOffset({240, 0});
    this->context.pieces[0][0]->SetToBox({0, 0});
    this->context.pieces[7][0] = new Rook(textureManager->GetItem("rook_black"), boxSize, Player::PLAYER_1);
    this->context.pieces[7][0]->SetOffset({240, 0});
    this->context.pieces[7][0]->SetToBox({0, 7});
    this->context.pieces[0][7] = new Rook(textureManager->GetItem("rook_white"), boxSize, Player::PLAYER_2);
    this->context.pieces[0][7]->SetOffset({240, 0});
    this->context.pieces[0][7]->SetToBox({7, 0});
    this->context.pieces[7][7] = new Rook(textureManager->GetItem("rook_black"), boxSize, Player::PLAYER_1);
    this->context.pieces[7][7]->SetOffset({240, 0});
    this->context.pieces[7][7]->SetToBox({7, 7});

    this->context.pieces[0][1] = new Knight(textureManager->GetItem("knight_white"), boxSize, Player::PLAYER_2);
    this->context.pieces[0][1]->SetOffset({240, 0});
    this->context.pieces[0][1]->SetToBox({1, 0});
    this->context.pieces[7][1] = new Knight(textureManager->GetItem("knight_black"), boxSize, Player::PLAYER_1);
    this->context.pieces[7][1]->SetOffset({240, 0});
    this->context.pieces[7][1]->SetToBox({1, 7});
    this->context.pieces[0][6] = new Knight(textureManager->GetItem("knight_white"), boxSize, Player::PLAYER_2);
    this->context.pieces[0][6]->SetOffset({240, 0});
    this->context.pieces[0][6]->SetToBox({6, 0});
    this->context.pieces[7][6] = new Knight(textureManager->GetItem("knight_black"), boxSize, Player::PLAYER_1);
    this->context.pieces[7][6]->SetOffset({240, 0});
    this->context.pieces[7][6]->SetToBox({6, 7});

    this->context.pieces[0][2] = new Bishop(textureManager->GetItem("bishop_white"), boxSize, Player::PLAYER_2);
    this->context.pieces[0][2]->SetOffset({240, 0});
    this->context.pieces[0][2]->SetToBox({2, 0});
    this->context.pieces[7][2] = new Bishop(textureManager->GetItem("bishop_black"), boxSize, Player::PLAYER_1);
    this->context.pieces[7][2]->SetOffset({240, 0});
    this->context.pieces[7][2]->SetToBox({2, 7});
    this->context.pieces[0][5] = new Bishop(textureManager->GetItem("bishop_white"), boxSize, Player::PLAYER_2);
    this->context.pieces[0][5]->SetOffset({240, 0});
    this->context.pieces[0][5]->SetToBox({5, 0});
    this->context.pieces[7][5] = new Bishop(textureManager->GetItem("bishop_black"), boxSize, Player::PLAYER_1);
    this->context.pieces[7][5]->SetOffset({240, 0});
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
    for (const auto &row : this->context.player1CaptureSprites)
        for (const auto &block : row)
            this->context.window->draw(block);

    for (const auto &row : this->context.player2CaptureSprites)
        for (const auto &block : row)
            this->context.window->draw(block);

    for (const auto &row : this->context.player1CapturedPieces)
        for (const auto &piece : row)
            if (piece)
                piece->Draw(this->context.window);

    for (const auto &row : this->context.player2CapturedPieces)
        for (const auto &piece : row)
            if (piece)
                piece->Draw(this->context.window);

    for (const auto &row : this->context.boardSprites)
        for (const auto &block : row)
            this->context.window->draw(block);

    for (const auto &row : this->context.pieces)
        for (const auto &piece : row)
            if (piece)
                piece->Draw(this->context.window);

    HierarchicalStateMachine::Draw();
}