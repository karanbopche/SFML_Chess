#pragma once

#include <StateMachine/StackedStateMachine.h>
#include <SFML/Graphics.hpp>

enum GameStateKeys
{
    MainMenuStateKey,
    ChessStateKey,
    PauseMenuStateKey
};

struct GameContext
{
    sf::RenderWindow *window;
};

class GameStateMachine : public StackedStateMachine<GameStateKeys>
{
public:
    explicit GameStateMachine(sf::RenderWindow *window);

protected:
    void InitStates();
    GameContext context;
};
