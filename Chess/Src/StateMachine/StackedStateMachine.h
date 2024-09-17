#pragma once

#include <map>
#include <stack>
#include <memory>
#include <SFML/Window.hpp>
#include "StackedState.h"

template <typename EStackedState>
class StackedStateMachine
{
public:

    inline void RegisterState(EStackedState key, std::unique_ptr<StackedState<EStackedState>> state)
    {
        stateRegistery[key] = std::move(state);
    }

    virtual inline void Start(EStackedState key)
    {
        states.push(stateRegistery[key].get());
        states.top()->EnterState();
    }

    virtual inline void EventHandler(sf::Event &event)
    {
        states.top()->EventHandler(event);
    }

    virtual inline void Update()
    {
        states.top()->Update();
    }

    virtual inline void Draw()
    {
        states.top()->Draw();
    }

    void StateTransition()
    {
        auto operation = states.top()->GetStackOperation();
        auto nextState = states.top()->GetNextState();
        states.top()->ClearNextState();
        states.top()->ClearStackOperation();

        switch (operation)
        {
        case StackedState<EStackedState>::StackOperation::None:
            break;
        case StackedState<EStackedState>::StackOperation::Push:
            states.top()->SuspendState();
            states.push(stateRegistery[nextState].get());
            states.top()->EnterState();
            break;
        case StackedState<EStackedState>::StackOperation::Pop:
            states.top()->ExitState();
            states.pop();
            states.top()->WakeUpState();
            break;
        case StackedState<EStackedState>::StackOperation::Switch:
            states.top()->ExitState();
            states.push(stateRegistery[nextState].get());
            states.top()->EnterState();
            break;
        }
    }

protected:
    std::map<EStackedState, std::unique_ptr<StackedState<EStackedState>>> stateRegistery;
    std::stack<StackedState<EStackedState> *> states;
};
