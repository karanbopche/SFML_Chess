#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <ChessStateMachine/ChessStateMachine.h>
#include <GameStateMachine/GameStateMachine.h>

class Game: sf::NonCopyable
{
public:
    Game();
    void Run();
    ~Game() = default;

protected:
    void InitWindow();
    void InitSound();

    void EventHandler(sf::Event& event);

    sf::Clock clock;
    sf::Music music;

    sf::RenderWindow window;
    std::unique_ptr<GameStateMachine> gameStateMachine;
};