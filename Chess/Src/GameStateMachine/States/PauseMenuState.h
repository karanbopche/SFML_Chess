#pragma once

#include "GameState.h"

class PauseMenuState : public GameState
{
public:
    PauseMenuState(GameContext &context);
    virtual void EnterState() override;
    virtual void ExitState() override;
    virtual void EventHandler(sf::Event &event) override;
    virtual void Update() override;
    virtual void Draw() override;
    virtual void SuspendState() override;
    virtual void WakeUpState() override;

protected:
};
