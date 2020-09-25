#pragma once
#include <memory>
#include <stack>

#include "State.hpp"

typedef std::unique_ptr<State> StateRef;

class StateMachine
{
public:
	StateMachine() {};
	~StateMachine() {};

	StateRef& getCurrentState();

	void addState(StateRef newState);
	void replaceState(StateRef newState);
	void removeState();

	void processStateChanges();

private:
	std::stack<StateRef> _states;
	StateRef _newState;
	bool _isAdding = false;
	bool _isReplacing = false;
	bool _isRemoving = false;
};