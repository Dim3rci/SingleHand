
#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp"

class Parser {
  public:
    Parser(Lexer& lexer) : lexer(lexer) {};

  private:
    Lexer& lexer;
};

#endif