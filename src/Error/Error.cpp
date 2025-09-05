#include "Error/Error.hpp"

// Base Error implementation

/**
 * @brief Constructs an Error object.
 */
Error::Error(std::string msg, int line, int column) noexcept
    : message(std::move(msg)), line(line), column(column)
{}

/**
 * @brief Returns the error message.
 */
std::string_view Error::what() const noexcept {
    return message;
}

/**
 * @brief Gets the line number.
 */
int Error::getLine() const noexcept {
    return line;
}

/**
 * @brief Gets the column number.
 */
int Error::getColumn() const noexcept {
    return column;
}

// LexerError implementation

/**
 * @brief Constructs a LexerError object.
 */
LexerError::LexerError(std::string msg, std::string filename, int line, int column) noexcept
    : Error(std::move(msg), line, column), filename_(std::move(filename))
{}

/**
 * @brief Returns the formatted error message.
 */
std::string_view LexerError::what() const noexcept {
    static thread_local std::string formatted_message;
    formatted_message = filename_
      + ":" + std::to_string(getLine())
      + ":" + std::to_string(getColumn())
      + ": " + std::string(Error::what());
    return formatted_message;
}

// FileError implementation

/**
 * @brief Constructs a FileError object.
 */
FileError::FileError(std::string msg, std::string fname) noexcept
    : Error(std::move(msg)), filename(std::move(fname))
{}

/**
 * @brief Returns the formatted error message.
 */
std::string_view FileError::what() const noexcept {
    static thread_local std::string formatted_message;

    formatted_message = "File error: " + message + " (file: " + filename + ")";
    return formatted_message;
}

/**
 * @brief Gets the filename associated with the error.
 */
std::string_view FileError::getFilename() const noexcept {
    return filename;
}
