#include <iostream>
#include <cstring>
#include "parameters.h"

void deadlock_set(char *arg){
    if ( !strcmp(arg, "true") ) deadlock_on = true;
    else if ( !strcmp(arg, "false") ) deadlock_on = false;
    else {
        std::cout << "ERROR: Bad Deadlock Parameter" << std::endl;
    }
}
