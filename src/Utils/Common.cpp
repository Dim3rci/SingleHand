#include "Utils/Common.hpp"
#include <fstream>
#include "Error/Error.hpp"

std::string Common::fileToString(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        throw Error("Could not open file: " + filename);
    }

    const std::streamsize size = file.tellg();
    if (size < 0) {
        throw Error("Could not determine file size: " + filename);
    }
    file.seekg(0, std::ios::beg);

    std::string buffer(static_cast<size_t>(size), '\0');
    if (!file.read(buffer.data(), size)) {
        throw Error("Could not read file: " + filename);
    }
    return buffer;
}
