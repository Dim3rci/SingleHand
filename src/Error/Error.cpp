#include "Error/Error.hpp"

Error::Error(const std::string& msg)
    : message(msg)
{}

std::string Error::what() const {
    return message;
}
