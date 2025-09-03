#include "parseError.hpp"

std::string ParseError::format(size_t line, const std::string& msg) {
    return "[Line " + std::to_string(line) + "] " + msg;
}