#pragma once

#include <string>
#include <stdexcept>
#include <map>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <optional>

enum TokenType { 
    VAR,       // 'v'
    NUMBER,    // Interger
    EGAL,      // #
    PLUS,      // '##'
    END        // end of input
};  

struct Token {
    TokenType type;
    std::string value;
};