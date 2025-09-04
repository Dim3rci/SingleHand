#include "Lexer/TokenStream.hpp"
#include <stdexcept>

// Constructor initializes lexer_ with the file, buffer_ empty
TokenStream::TokenStream(const std::string& filename)
    : lexer_(filename), buffer_(std::nullopt) {}

// If buffer_ is empty, fetch the next token from lexer_
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

const Token& TokenStream::peek() {
    fillBuffer();
    return *buffer_;
}

Token TokenStream::next() {
    fillBuffer();
    Token current = std::move(*buffer_);
    buffer_.reset();
    return current;
}

bool TokenStream::hasNext() {
    fillBuffer();
    return buffer_->getType() != TokenType::END;
}
