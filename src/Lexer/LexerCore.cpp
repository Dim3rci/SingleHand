#include <stdexcept>
#include <cctype>
#include <iostream>
#include <array>
#include <functional>
#include <vector>

#include "Lexer/LexerCore.hpp"
#include "Error/Error.hpp"

/**
 * @brief Constructs a LexerCore object from a file.
 */
LexerCore::LexerCore(const std::string& filename) {
    filename_ = filename;
    input_ = Common::fileToString(filename);
    pos_ = 0;
    line_ = 1;
    column_ = 1;
}

// Fast ASCII lookup tables for isalpha, isalnum, isdigit
namespace {
    constexpr auto make_alpha_table() {
        std::array<bool, 256> t{};
        for (int i = 0; i < 256; ++i)
            t[i] = (i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z') || (i == '_');
        return t;
    }
    constexpr auto make_alnum_table() {
        std::array<bool, 256> t{};
        for (int i = 0; i < 256; ++i)
            t[i] = (i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z') || (i == '_')
                   || (i >= '0' && i <= '9');
        return t;
    }
    constexpr auto make_digit_table() {
        std::array<bool, 256> t{};
        for (int i = 0; i < 256; ++i)
            t[i] = (i >= '0' && i <= '9');
        return t;
    }

    constexpr auto is_alpha_table = make_alpha_table();
    constexpr auto is_alnum_table = make_alnum_table();
    constexpr auto is_digit_table = make_digit_table();

    inline bool is_alpha(unsigned char c) { return is_alpha_table[c]; }
    inline bool is_alnum(unsigned char c) { return is_alnum_table[c]; }
    inline bool is_digit(unsigned char c) { return is_digit_table[c]; }
    inline bool is_space(unsigned char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }
}

std::string_view LexerCore::getInput() const {
    /**
     * @brief Returns the input string.
     */
    return input_;
}

std::pair<int, int> LexerCore::getCurrentPos() const {
    /**
     * @brief Gets the current line and column position.
     */
    return {line_, column_};
}

void LexerCore::skipWhitespace(const char* data, size_t size, size_t& p, int& line, int& column) {
    /**
     * @brief Skips whitespace characters in the input.
     */
    while (p < size) {
        unsigned char c = static_cast<unsigned char>(data[p]);
        if (c == ' ' || c == '\t') {
            ++p; ++column;
        } else if (c == '\n') {
            ++p; ++line; column = 1;
        } else if (c == '\r') {
            ++p; if (p < size && data[p] == '\n') ++p;
            ++line; column = 1;
        } else {
            break;
        }
    }
}

Token LexerCore::lexIdentifier(const char* data, size_t size, size_t& p, int& line, int& column) {
    /**
     * @brief Lexes an identifier token.
     */
    size_t start = p;

    ++p; ++column;  // we know data[start] is alpha or '_'
    while (p < size && is_alnum(static_cast<unsigned char>(data[p]))) {
        ++p; ++column;
    }
    return Token{TokenType::IDENTIFIER, std::string_view(data + start, p - start)};
}

Token LexerCore::lexNumber(const char* data, size_t size, size_t& p, int& line, int& column) {
    /**
     * @brief Lexes a number token.
     */
    size_t start = p;

    ++p; ++column;  // we know data[start] is digit
    while (p < size && is_digit(static_cast<unsigned char>(data[p]))) {
        ++p; ++column;
    }
    return Token{TokenType::NUMBER, std::string_view(data + start, p - start)};
}

std::optional<Token> LexerCore::lexOperator(const char* data, size_t size, size_t& p, int& line, int& column) {
    /**
     * @brief Lexes an operator token.
     */
    unsigned char c = static_cast<unsigned char>(data[p]);

    if (c == '#') {
        if (p + 1 < size && data[p+1] == '#') {
            p += 2; column += 2;
            return Token{TokenType::PLUS, std::string_view("##",2)};
        }
        p += 1; column += 1;
        return Token{TokenType::EQUAL, std::string_view("#",1)};
    }
    return std::nullopt;
}

std::optional<Token> LexerCore::nextToken() {
    /**
     * @brief Returns the next token from the input.
     */
    const char* data   = input_.data();
    size_t      size   = input_.size();
    size_t      p      = pos_;
    int         line   = line_;
    int         column = column_;

    skipWhitespace(data, size, p, line, column);

    if (p >= size) {
        pos_ = p; line_ = line; column_ = column;
        return Token{TokenType::END, {}};
    }

    unsigned char c = static_cast<unsigned char>(data[p]);
    int currentLine   = line, currentColumn = column;

    if (is_alpha(c)) {
        Token tok = lexIdentifier(data, size, p, line, column);
        pos_ = p; line_ = line; column_ = column;
        return tok;
    }
    if (is_digit(c)) {
        Token tok = lexNumber(data, size, p, line, column);
        pos_ = p; line_ = line; column_ = column;
        return tok;
    }
    if (auto op = lexOperator(data, size, p, line, column)) {
        pos_ = p; line_ = line; column_ = column;
        return *op;
    }

    throw LexerError(std::string("Unexpected character: ") + static_cast<char>(c),
                        filename_, currentLine, currentColumn);
}
