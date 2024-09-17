#pragma once

#include <SFML/Window.hpp>

template <typename EHierarchicalState>
class HierarchicalState
{
public:
    HierarchicalState(EHierarchicalState key) : key(key), nextState(key) {}
    virtual ~HierarchicalState() = default;
    inline EHierarchicalState getKey() { return this->key; }
    inline EHierarchicalState GetNextState(){ return this->nextState; }
    inline void ClearNextState() { this->nextState = this->key; }

    virtual void EnterState() = 0;
    virtual void ExitState() = 0;
    virtual void EventHandler(sf::Event &event) = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;

protected:
    inline void SetNextState(const EHierarchicalState state) { this->nextState = state; }
    const EHierarchicalState key;
    EHierarchicalState nextState;
};
