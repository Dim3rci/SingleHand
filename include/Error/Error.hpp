#pragma once
#include <string>
#include <string_view>

/**
 * @brief Base error class - optimized for minimal overhead.
 */
class Error {
    protected:
        std::string message;
        int         line;
        int         column;

        public:
        /**
         * @brief Constructs an Error object.
         * @param msg Error message.
         * @param line Line number (optional).
         * @param column Column number (optional).
         */
        explicit Error(std::string msg, int line = 0, int column = 0) noexcept;

        /**
         * @brief Virtual destructor.
         */
        virtual ~Error() = default;

        /**
         * @brief Returns the error message.
         * @return Error message as std::string_view.
         */
        virtual std::string_view what() const noexcept;

        /**
         * @brief Gets the column number.
         * @return Column number.
         */
        int getColumn() const noexcept;

        /**
         * @brief Gets the line number.
         * @return Line number.
         */
        int getLine() const noexcept;
};

/**
 * @brief Specialized error for lexer issues - includes position information.
 */
class LexerError final : public Error {
    public:
        /**
         * @brief Constructs a LexerError object.
         * @param msg Error message.
         * @param filename Filename where the error occurred.
         * @param line Line number.
         * @param column Column number.
         */
        explicit LexerError(std::string msg, std::string filename, int line, int column) noexcept;

        /**
         * @brief Returns the formatted error message.
         * @return Error message as std::string_view.
         */
        std::string_view what() const noexcept override;
    private:
        std::string filename_;
};

/**
 * @brief Specialized error for file operations - includes filename.
 */
class FileError final : public Error {
    private:
        std::string filename;
    public:
        /**
         * @brief Constructs a FileError object.
         * @param msg Error message.
         * @param filename Filename related to the error.
         */
        explicit FileError(std::string msg, std::string filename) noexcept;

        /**
         * @brief Returns the formatted error message.
         * @return Error message as std::string_view.
         */
        std::string_view what() const noexcept override;

        /**
         * @brief Gets the filename associated with the error.
         * @return Filename as std::string_view.
         */
        std::string_view getFilename() const noexcept;
};
