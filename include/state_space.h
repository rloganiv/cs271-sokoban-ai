#ifndef STATE_SPACE_H
#define STATE_SPACE_H

#include "state.h"
#include "problem.h"

struct State_Space
{
	State current; // Current state
	Action parent_to_curr; // Move that led from parent to current state
	State_Space *parent; // Parent of current state
};

#endif


