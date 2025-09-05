#pragma once

#include "Lexer/LexerCore.hpp"
#include <optional>
#include <string>
#include <string_view>

/**
 * @brief Stream interface for consuming tokens from a lexer.
 */
class TokenStream {
public:
    /**
     * @brief Constructs a TokenStream from a filename.
     * @param filename Name of the file to tokenize.
     */
    explicit TokenStream(const std::string& filename);

    /**
     * @brief Consume and return the next token.
     * @return Next token.
     */
    Token next();

    /**
     * @brief Checks if there are more tokens (END not yet reached).
     * @return True if more tokens are available.
     */
    bool hasNext();

private:
    /**
     * @brief Fills the buffer with the next token if empty.
     */
    void fillBuffer();

    LexerCore            lexer_;
    std::optional<Token> buffer_;
};
