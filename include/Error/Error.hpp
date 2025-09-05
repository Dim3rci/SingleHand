#pragma once
#include <string>
#include <string_view>

// Base error class - optimized for minimal overhead
class Error {
    protected:
        std::string message;
        int         line;
        int         column;

        public:
        explicit Error(std::string msg, int line = 0, int column = 0) noexcept;
        virtual ~Error() = default;

        virtual std::string_view what() const noexcept;
        int getColumn() const noexcept;
        int getLine() const noexcept;
};

// Specialized error for lexer issues - includes position information
class LexerError final : public Error {
    public:
        explicit LexerError(std::string msg, std::string filename, int line, int column) noexcept;
        std::string_view what() const noexcept override;
    private:
        std::string filename_;
};

// Specialized error for file operations - includes filename
class FileError final : public Error {
    private:
        std::string filename;
    public:
        explicit FileError(std::string msg, std::string filename) noexcept;
        std::string_view what() const noexcept override;
        std::string_view getFilename() const noexcept;
};
