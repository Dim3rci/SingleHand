#pragma once

#include <optional>
#include <string_view>
#include <cctype>

#include "Utils/Common.hpp"
#include "Lexer/Token.hpp"

class LexerCore {
    public:
        explicit LexerCore(const std::string& filename);
        std::string_view getInput() const;
        std::optional<Token> nextToken();
        
    private:
        std::string input_;
        size_t pos_;
};
