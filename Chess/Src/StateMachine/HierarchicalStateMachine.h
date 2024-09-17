#pragma once

#include <map>
#include <memory>
#include <SFML/Window.hpp>
#include "HierarchicalState.h"

template <typename EHierarchicalState>
class HierarchicalStateMachine
{
public:
    HierarchicalStateMachine() = default;
    virtual ~HierarchicalStateMachine() = default;
    
    inline void RegisterState(EHierarchicalState key, std::unique_ptr<HierarchicalState<EHierarchicalState>> state)
    {
        this->states[key] = std::move(state);
    }

    virtual inline void Start()
    {
        this->states[this->currentState]->EnterState();
    }

    virtual inline void EventHandler(sf::Event &event)
    {
        this->states[this->currentState]->EventHandler(event);
    }

    virtual inline void Update()
    {
        states[this->currentState]->Update();
    }

    virtual inline void Draw()
    {
        this->states[this->currentState]->Draw();
    }

    inline void StateTransition()
    {
        auto nextState = states[this->currentState]->GetNextState();
        states[this->currentState]->ClearNextState();
        if (nextState != currentState)
        {
            states[this->currentState]->ExitState();
            this->currentState = nextState;
            states[this->currentState]->EnterState();
        }
    }

protected:
    std::map<EHierarchicalState, std::unique_ptr<HierarchicalState<EHierarchicalState>>> states;
    EHierarchicalState currentState;
};
