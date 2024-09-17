#pragma once

#include <SFML/Window.hpp>

template <typename EStackedState>
class StackedState
{
public:
    enum class StackOperation
    {
        None,
        Push,
        Pop,
        Switch
    };
    StackedState(EStackedState key) : key(key), nextState(key) {}

    inline EStackedState getKey()
    {
        return this->key;
    }
    
    inline EStackedState GetNextState()
    {
        return this->nextState;
    }
    
    inline StackOperation GetStackOperation()
    {
        return this->operation;
    }

    inline void ClearNextState()
    {
        this->nextState = this->key;
    }
    
    inline void ClearStackOperation()
    {
        this->operation = StackOperation::None;
    }

    virtual void EnterState() = 0;
    virtual void ExitState() = 0;
    virtual void SuspendState() = 0;
    virtual void WakeUpState() = 0;

    virtual void EventHandler(sf::Event &event) = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;

protected:

    inline void SwitchState(const EStackedState state)
    {
        this->operation = StackOperation::Switch;
        this->nextState = state;
    }

    inline void PushState(const EStackedState state)
    {
        this->operation = StackOperation::Push;
        this->nextState = state;
    }

    inline void PopState() { this->operation = StackOperation::Pop; }

private:
    const EStackedState key;
    EStackedState nextState;
    StackOperation operation;
};
