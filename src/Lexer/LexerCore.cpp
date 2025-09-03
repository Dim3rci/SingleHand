#include "Lexer/LexerCore.hpp"
#include <stdexcept>
#include <cctype>

LexerCore::LexerCore(const std::string& filename) {
    input_ = Common::fileToString(filename);
    pos_ = 0;
}

void LexerCore::skipWhitespace() {
    while (pos_ < input_.size() && std::isspace(static_cast<unsigned char>(input_[pos_])))
        ++pos_;
}

std::string_view LexerCore::getInput() const {
    return input_;
}

std::optional<Token> LexerCore::nextToken() {
    skipWhitespace();

    if (pos_ >= input_.size()) {
        return Token{TokenType::END, std::string_view("")};
    }

    char c = input_[pos_];

    if (c == 'v') {
        ++pos_;
        if (pos_ >= input_.size() || !std::isspace(static_cast<unsigned char>(input_[pos_]))) {
            throw std::runtime_error("Expected space after 'v'");
        }
        ++pos_; // skip space
        size_t start = pos_;
        while (pos_ < input_.size() && !std::isspace(static_cast<unsigned char>(input_[pos_]))) {
            ++pos_;
        }
        if (start == pos_) {
            throw std::runtime_error("Missing identifier after 'v '");
        }
        std::string_view val(input_.data() + start, pos_ - start);
        return Token{TokenType::VAR, val};
    }

    if (std::isdigit(static_cast<unsigned char>(c))) {
        size_t start = pos_;
        while (pos_ < input_.size() && std::isdigit(static_cast<unsigned char>(input_[pos_]))) {
            ++pos_;
        }
        std::string_view val(input_.data() + start, pos_ - start);
        return Token{TokenType::NUMBER, val};
    }

    if (c == '#') {
        if (pos_ + 1 < input_.size() && input_[pos_ + 1] == '#') {
            pos_ += 2;
            return Token{TokenType::PLUS, std::string_view("+")};
        }
        ++pos_;
        return Token{TokenType::EQUAL, std::string_view("=")};
    }

    throw std::runtime_error(std::string("Unexpected character: ") + c);
}
