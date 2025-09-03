#pragma once
#include <string>

class Error {
protected:
    std::string message;
public:
    explicit Error(const std::string& msg);
    virtual ~Error() = default;

    virtual std::string what() const;
};
