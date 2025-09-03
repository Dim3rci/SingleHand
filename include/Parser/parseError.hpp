#ifndef PARSE_ERROR_HPP
#define PARSE_ERROR_HPP

#include "commonType.hpp"

class ParseError : public std::runtime_error {
    public:
        ParseError(size_t line, const std::string& msg) : std::runtime_error(format(line, msg)) {}

    private:
        std::string format(size_t line, const std::string& msg);
};

#endif