#pragma once

#include "Lexer/LexerCore.hpp"
#include <optional>
#include <string>
#include <string_view>

class TokenStream {
public:
    // Construct by filename; lexer_ reads and holds the entire input
    explicit TokenStream(const std::string& filename);

    // Look at next token without consuming
    [[nodiscard]] const Token& peek();

    // Consume and return the next token
    Token next();

    // True if there are more tokens (END not yet reached)
    bool hasNext();

private:
    // Fill buffer_ if empty
    void fillBuffer();

    LexerCore lexer_;
    std::optional<Token> buffer_;
};
