#include "lexer.hpp"

Lexer::Lexer(const std::string_view& input)
    : input(input),
    pos(0)
{
}


void Lexer::skipWhitespace() {
    while (pos < input.size() && isspace(input[pos])) pos++;
}

std::optional<Token> Lexer::nextToken() {
    skipWhitespace();

    if (input[pos] == 'v') {
        pos++;
        std::string value;
        while (pos < input.size() && !isspace(input[pos])) {
            value += input[pos++];
        }
        return Token{TokenType::VAR, value};
    }

    if (isdigit(input[pos])) {
        std::string value;
        while (pos< input.size() && isdigit(input[pos])) {
            value += input[pos++];
        }
        return Token{TokenType::NUMBER, value};
    
    }

    if (input[pos] == '#') {
        if (input[pos + 1] == '#') {
            pos += 2;
            return Token{TokenType::PLUS, "+"};
        }
        pos++;
        return Token{TokenType::EGAL, "="};
    }
    
    if (pos == input.size()) {
        return Token{TokenType::END, ""};
    }

    throw std::runtime_error("Unexpected character");
}
