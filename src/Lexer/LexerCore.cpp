#include <stdexcept>
#include <cctype>
#include <iostream>
#include <array>

#include "Lexer/LexerCore.hpp"

LexerCore::LexerCore(const std::string& filename) {
    input_ = Common::fileToString(filename);
    pos_ = 0;
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
    return input_;
}

std::optional<Token> LexerCore::nextToken() {
    const char* data = input_.data();
    size_t size = input_.size();
    size_t p = pos_;

    // Skip whitespace (fast loop)
    while (p < size && is_space(static_cast<unsigned char>(data[p]))) ++p;

    if (p >= size) {
        pos_ = p;
        return Token{TokenType::END, std::string_view()};
    }

    unsigned char c = static_cast<unsigned char>(data[p]);

    // Identifier (variable or keyword)
    if (is_alpha(c)) {
        size_t start = p;
        do { ++p; } while (p < size && is_alnum(static_cast<unsigned char>(data[p])));
        pos_ = p;
        return Token{TokenType::IDENTIFIER, std::string_view(data + start, p - start)};
    }

    // Number
    if (is_digit(c)) {
        size_t start = p;
        do { ++p; } while (p < size && is_digit(static_cast<unsigned char>(data[p])));
        pos_ = p;
        return Token{TokenType::NUMBER, std::string_view(data + start, p - start)};
    }

    // Operators + and =
    if (c == '#') {
        if (p + 1 < size && data[p + 1] == '#') {
            pos_ = p + 2;
            return Token{TokenType::PLUS, std::string_view("+")};
        }
        pos_ = p + 1;
        return Token{TokenType::EQUAL, std::string_view("=")};
    }

    // ...add more operators/symbols as needed...

    throw std::runtime_error(std::string("Unexpected character: ") + static_cast<char>(c));
}
