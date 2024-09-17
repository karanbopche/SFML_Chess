#pragma once

#include <StateMachine/StackedStateMachine.h>
#include "../GameStateMachine.h"

class GameState : public StackedState<GameStateKeys>
{
public:
    explicit inline GameState(GameContext &context, GameStateKeys key) : StackedState(key), context(context) {};

protected:
    GameContext &context;
};