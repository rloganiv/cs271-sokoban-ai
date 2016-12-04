#ifndef DEADLOCK_H
#define DEADLOCK_H

#include "state.h"
#include <vector>
#include <queue>

bool* get_simple_deadlocks(State* s);
bool freeze_check(State* s, bool* deadlock_arr, Coord coord);

#endif
