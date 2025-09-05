#include <iostream>
#include <string>

#include "Lexer/LexerCore.hpp"
#include "Lexer/TokenStream.hpp"
#include "Utils/Common.hpp"
#include "Error/Error.hpp"

// helper to stringify token types
static std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::IDENTIFIER:    return "IDENTIFIER";
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::EQUAL:  return "EQUAL";
        case TokenType::PLUS:   return "PLUS";
        case TokenType::END:    return "END";
    }
    return "UNKNOWN";
}

int main(int argc, char* argv[]) {
    std::string filename = (argc > 1 ? argv[1] : "syntaxe.txt");

    try {
        TokenStream ts(filename);
        while (ts.hasNext()) {
            Token tok = ts.next();
            std::cout 
                << tokenTypeToString(tok.getType()) 
                << ": '" << tok.getValue() << "'\n";
        }
    } catch (const Error& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}