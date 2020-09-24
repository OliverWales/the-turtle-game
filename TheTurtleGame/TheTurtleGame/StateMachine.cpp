#include "StateMachine.hpp"

#include <iostream>

void StateMachine::addState(StateRef newState) {
	_isAdding = true;
	_isReplacing = false;
	_isRemoving = false;
	_newState = std::move(newState);
}

void StateMachine::replaceState(StateRef newState) {
	_isAdding = false;
	_isReplacing = true;
	_isRemoving = false;
	_newState = std::move(newState);
}

void StateMachine::removeState()
{
	_isAdding = false;
	_isReplacing = false;
	_isRemoving = true;
}

void StateMachine::processStateChanges()
{
	if (_isRemoving)
	{
		// pop current state
		if (!_states.empty())
		{
			_states.pop();
			std::cout << "State removed" << std::endl;
		}
		_isRemoving = false;
	}
	else if (_isReplacing)
	{
		// pop current state
		if (!_states.empty())
		{
			_states.pop();
		}

		// set new current state
		_states.push(std::move(_newState));
		std::cout << "State replaced" << std::endl;
		_isReplacing = false;
	}
	else if (_isAdding)
	{
		// set new current state
		_states.push(std::move(_newState));
		std::cout << "State added" << std::endl;
		_isAdding = false;
	}
}

StateRef& StateMachine::getCurrentState()
{
	return _states.top();
}
