
#ifndef PARSER_HPP
#define PARSER_HPP

#include "Lexer/LexerCore.hpp"

class Parser {
  public:
    Parser(LexerCore& lexer) : lexer(lexer) {};

  private:
    LexerCore& lexer;
};

#endif