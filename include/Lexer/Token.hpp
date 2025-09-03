#pragma once

#include <string>
#include <cstdint>

enum class TokenType : std::uint8_t {
    VAR,
    NUMBER,
    EQUAL,
    PLUS,
    END
};

//class
class Token {
    public:
        constexpr Token(TokenType type, std::string_view value) noexcept
            : type_(type), value_(value) {}

        constexpr TokenType getType() const noexcept { return type_; }
        constexpr const std::string_view& getValue() const noexcept { return value_; }

    private:
        TokenType type_;
        std::string_view value_;
};