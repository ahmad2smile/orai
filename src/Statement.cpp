//
// Created by ahmad on 8/13/23.
//

#include <iostream>
#include "Statement.h"

namespace Orai {
    Orai::Statement::Statement(const char* raw) : raw(raw) {}
    
    void Statement::Debug() {
        std::cout << "Statement:: " << raw << std::endl;
    }
} // Orai
