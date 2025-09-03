#pragma once

#include "Utils/Common.hpp"
#include <optional>
#include <string_view>
#include <cctype>
#include "Lexer/Token.hpp"

class LexerCore {
    public:
        explicit LexerCore(const std::string& filename);
        void skipWhitespace();
        std::string_view getInput() const;
        std::optional<Token> nextToken();
  
    private:
      std::string input_;
      size_t pos_;
      // std::vector<Token> tokens;
};
