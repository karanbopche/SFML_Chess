#include "MainMenuState.h"
#include <Manager/FontManager.h>
#include <Manager/TextureManager.h>


MainMenuState::MainMenuState(GameContext &context) : HierarchicalState(GameStateKeys::ChessStateKey, context)
{
    this->InitMenuItems();
}

void MainMenuState::EnterState()
{
}
void MainMenuState::ExitState()
{
}
void MainMenuState::EventHandler(sf::Event &event)
{
    this->start.EventHandler(event);
    this->exit.EventHandler(event);
}
void MainMenuState::Update()
{
}
void MainMenuState::Draw()
{
    this->start.Draw(this->context.window);
    this->exit.Draw(this->context.window);
}

void MainMenuState::InitMenuItems()
{
const auto &font = FontManager::GetInstance()->GetItem("default");

    this->start.SetFont(font);
    this->start.SetText("Start Game");
    this->start.SetOriginToCenter();
    this->start.SetPosition({100, 600});
    this->exit.SetFont(font);
    this->exit.SetText("Exit");
    this->exit.SetOriginToCenter();
    this->exit.SetPosition({100, 600});
    
    this->start.SetOnClickCallback(
        [this](){
            this->SetNextState(GameStateKeys::ChessStateKey);
        }
    );
    this->exit.SetOnClickCallback(
        [this](){
            this->context.window->close();
        }
    );

    auto textureManager = TextureManager::GetInstance();
    this->backgroundBox[0].setTexture(textureManager->GetItem("board-black"));
    this->backgroundBox[1].setTexture(textureManager->GetItem("board-white"));
}
