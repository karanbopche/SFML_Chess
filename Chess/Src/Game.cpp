#include "Game.h"
#include "config.h"

Game::Game()
{
    this->InitWindow();
    this->InitSound();
    this->chessStateMachine = std::make_unique<ChessStateMachine>(this->window.get());
    this->chessStateMachine->Start();
}

void Game::InitWindow()
{
    auto config = Config::GetInstance();
    this->window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(config->GetConfigInt("window", "width"), config->GetConfigInt("window", "height")),
        config->GetConfigString("window", "title"));
    this->window->setFramerateLimit(config->GetConfigInt("window", "frame_rate_limit"));
}

void Game::InitSound()
{
    auto config = Config::GetInstance();
    this->music.openFromFile(config->GetConfigString("music", "background"));
    this->music.setLoop(true);
}

void Game::EventHandler(sf::Event &event)
{
    if (event.type == sf::Event::Closed)
    {
        this->window->close();
    }
    this->chessStateMachine->EventHandler(event);
}

void Game::Run()
{
    sf::Event event;
    this->music.play();
    while (this->window->isOpen())
    {
        while (this->window->pollEvent(event))
        {
            this->EventHandler(event);
        }
        this->chessStateMachine->Update();
        
        this->window->clear();
        this->chessStateMachine->Draw();
        this->window->display();
        this->chessStateMachine->StateTransition();
    }
}