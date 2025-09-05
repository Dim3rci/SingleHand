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
        std::string filename_;
        std::string input_;
        size_t      pos_;
        int         line_;
        int         column_;

        // Helper method to get current position info
        std::pair<int, int> getCurrentPos() const;

        void skipWhitespace(const char* data, size_t size, size_t& p, int& line, int& column);
        Token lexIdentifier(const char* data, size_t size, size_t& p, int& line, int& column);
        Token lexNumber    (const char* data, size_t size, size_t& p, int& line, int& column);
        std::optional<Token> lexOperator(const char* data, size_t size, size_t& p, int& line, int& column);
};
