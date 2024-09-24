#pragma once

#include <StateMachine/HierarchicalState.h>
#include "../GameStateMachine.h"

class PauseMenuState : public HierarchicalState<GameStateKeys, GameContext>
{
public:
    PauseMenuState(GameContext &context);
    virtual void EnterState() override;
    virtual void ExitState() override;
    virtual void EventHandler(sf::Event &event) override;
    virtual void Update() override;
    virtual void Draw() override;
protected:
};
