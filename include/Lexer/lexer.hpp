#pragma once

#include "commonType.hpp"

class Lexer {
    private:
      std::string_view input;
      size_t pos;
      // std::vector<Token> tokens;
  
    public:
      Lexer(const std::string_view& input);

      void skipWhitespace();
      std::optional<Token> nextToken();
};
