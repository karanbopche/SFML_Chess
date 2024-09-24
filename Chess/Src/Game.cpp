#include "Game.h"
#include "config.h"

Game::Game()
{
    this->InitWindow();
    this->InitSound();
    this->gameStateMachine = std::make_unique<GameStateMachine>(&this->window);
    this->gameStateMachine->Start();
}

void Game::InitWindow()
{
    auto config = Config::GetInstance();
    this->window.create(
        sf::VideoMode(config->GetConfigInt("window", "width"), config->GetConfigInt("window", "height")),
        config->GetConfigString("window", "title"));
    this->window.setFramerateLimit(config->GetConfigInt("window", "frame_rate_limit"));
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
        this->window.close();
    }
    this->gameStateMachine->EventHandler(event);
}

void Game::Run()
{
    sf::Event event;
    this->music.play();
    while (this->window.isOpen())
    {
        while (this->window.pollEvent(event))
        {
            this->EventHandler(event);
        }
        this->gameStateMachine->Update();
        
        this->window.clear();
        this->gameStateMachine->Draw();
        this->window.display();
        this->gameStateMachine->StateTransition();
    }
}