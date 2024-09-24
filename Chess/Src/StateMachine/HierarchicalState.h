#pragma once

#include <SFML/Window.hpp>

template <typename EHierarchicalState,  typename Context>
class HierarchicalState
{
public:
    HierarchicalState(EHierarchicalState key, Context &context) : key(key), nextState(key), context(context) {}
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
    Context &context;
};
