#pragma once

#include <string>
#include <cstdint>

/**
 * @brief Token types for the lexer.
 */
enum class TokenType : std::uint8_t {
    IDENTIFIER,
    NUMBER,
    EQUAL,
    PLUS,
    END
};

/**
 * @brief Represents a token produced by the lexer.
 */
class Token {
    public:
        /**
         * @brief Constructs a Token object.
         * @param type Type of the token.
         * @param value Value of the token.
         */
        constexpr Token(TokenType type, std::string_view value) noexcept
            : type_(type), value_(value) {}

        /**
         * @brief Gets the token type.
         * @return TokenType.
         */
        constexpr TokenType getType() const noexcept { return type_; }

        /**
         * @brief Gets the token value.
         * @return Token value as std::string_view.
         */
        constexpr const std::string_view& getValue() const noexcept { return value_; }

    private:
    TokenType        type_;
    std::string_view value_;
};