#pragma once

#include <optional>
#include <string_view>
#include <cctype>

#include "Utils/Common.hpp"
#include "Lexer/Token.hpp"

/**
 * @brief Core lexer class for tokenizing input.
 */
class LexerCore {
    public:
        /**
         * @brief Constructs a LexerCore object from a file.
         * @param filename Name of the file to tokenize.
         */
        explicit LexerCore(const std::string& filename);

        /**
         * @brief Returns the input string.
         * @return Input as std::string_view.
         */
        std::string_view getInput() const;

        /**
         * @brief Returns the next token from the input.
         * @return Next token, or std::nullopt if end of input.
         */
        std::optional<Token> nextToken();
        
    private:
        std::string filename_;
        std::string input_;
        size_t      pos_;
        int         line_;
        int         column_;

        /**
         * @brief Gets the current line and column position.
         * @return Pair of line and column.
         */
        std::pair<int, int> getCurrentPos() const;

        /**
         * @brief Skips whitespace characters in the input.
         * @param data Pointer to input data.
         * @param size Size of input data.
         * @param p Current position (modified).
         * @param line Current line (modified).
         * @param column Current column (modified).
         */
        void skipWhitespace(const char* data, size_t size, size_t& p, int& line, int& column);

        /**
         * @brief Lexes an identifier token.
         * @param data Pointer to input data.
         * @param size Size of input data.
         * @param p Current position (modified).
         * @param line Current line (modified).
         * @param column Current column (modified).
         * @return Identifier token.
         */
        Token lexIdentifier(const char* data, size_t size, size_t& p, int& line, int& column);

        /**
         * @brief Lexes a number token.
         * @param data Pointer to input data.
         * @param size Size of input data.
         * @param p Current position (modified).
         * @param line Current line (modified).
         * @param column Current column (modified).
         * @return Number token.
         */
        Token lexNumber(const char* data, size_t size, size_t& p, int& line, int& column);

        /**
         * @brief Lexes an operator token.
         * @param data Pointer to input data.
         * @param size Size of input data.
         * @param p Current position (modified).
         * @param line Current line (modified).
         * @param column Current column (modified).
         * @return Operator token or std::nullopt.
         */
        std::optional<Token> lexOperator(const char* data, size_t size, size_t& p, int& line, int& column);
};
