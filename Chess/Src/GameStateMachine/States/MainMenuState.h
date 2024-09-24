#pragma once

#include <StateMachine/HierarchicalState.h>
#include "../GameStateMachine.h"
#include <Widgets/Button.h>


class MainMenuState: public HierarchicalState<GameStateKeys, GameContext>
{
public:
    explicit MainMenuState(GameContext &context);
    virtual void EnterState() override;
    virtual void ExitState() override;
    virtual void EventHandler(sf::Event &event) override;
    virtual void Update() override;
    virtual void Draw() override;
protected:
    void InitMenuItems();

private:
    Button start;
    Button exit;
    sf::Text text;
    sf::CircleShape circle;
    sf::Sprite backgroundBox[2];
};