#include "tokenStream.hpp"

bool TokenStream::variableHasvalue(const std::string& name) {
    const size_t token_count = tokens.size();

    for (size_t i = 0; i < token_count; ++i) {
        if (tokens[i].value == name && i + 1 < token_count) {
            const Token& nextToken = tokens[i + 1];
            if (nextToken.type == TokenType::NUMBER) {
                return true;
            }
        }
    }
    return false;
}

bool TokenStream::variableExist(const std::string& name, int pos) {
    for (int i = 0; i < tokens.size(); ++i) {
        if (i != pos && tokens[i].value == name) {
            return true;
        }
    }
    return false;
}