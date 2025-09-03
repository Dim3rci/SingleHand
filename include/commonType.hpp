#ifndef COMMON_TYPE_HPP
#define COMMON_TYPE_HPP

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
    NUMBER,    // valeur numérique
    EGAL,      // #
    PLUS,      // '##'
    END        // fin d'entrée
};  

struct Token {
    TokenType type;
    std::string value;
};

#endif