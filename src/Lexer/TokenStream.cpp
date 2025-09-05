#include "Lexer/TokenStream.hpp"
#include <stdexcept>

/**
 * @brief Constructor initializes lexer_ with the file, buffer_ empty.
 */
TokenStream::TokenStream(const std::string& filename)
    : lexer_(filename), buffer_(std::nullopt) {}

/**
 * @brief If buffer_ is empty, fetch the next token from lexer_.
 */
void TokenStream::fillBuffer() {
    if (!buffer_) {
        auto tokOpt = lexer_.nextToken();
        if (tokOpt) {
            buffer_ = std::move(*tokOpt);
        } else {
            // In case lexer returns no token, treat as END
            buffer_ = Token{TokenType::END, std::string_view("")};
        }
    }
}

/**
 * @brief Consume and return the next token.
 */
Token TokenStream::next() {
    fillBuffer();
    Token current = std::move(*buffer_);
    buffer_.reset();
    return current;
}

/**
 * @brief True if there are more tokens (END not yet reached).
 */
bool TokenStream::hasNext() {
    fillBuffer();
    return buffer_->getType() != TokenType::END;
}
