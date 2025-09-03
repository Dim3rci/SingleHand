#pragma once

#include "commonType.hpp"

class TokenStream {
    private:
        std::vector<Token> tokens;
        size_t index;

    public:
        TokenStream(std::vector<Token> tokens) : tokens(std::move(tokens)) {}

        Token current() const { return tokens[index]; }
        Token next() { return tokens[++index]; }
        Token peek(size_t offset = 1) const { return tokens[index + offset]; }
        bool variableHasvalue(const std::string& name);
        bool hasNext() const { return index < tokens.size(); }
        bool variableExist(const std::string& name, int pos);
};