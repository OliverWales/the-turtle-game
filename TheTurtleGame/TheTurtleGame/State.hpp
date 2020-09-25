#pragma once

class State
{
public:
	virtual void update(float dt) = 0;
	virtual void stepAnimation() = 0;
	virtual void draw() = 0;
};