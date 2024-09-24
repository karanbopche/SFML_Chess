#pragma once

#include <StateMachine/HierarchicalStateMachine.h>
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

class GameStateMachine : public HierarchicalStateMachine<GameStateKeys, GameContext>
{
public:
    explicit GameStateMachine(sf::RenderWindow *window);

protected:
    void InitStates();
};
