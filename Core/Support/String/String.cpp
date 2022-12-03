#include <cstring>
#include <string>
#include <vector>
#include "String.h"

std::vector<std::string> String::explode(const std::string &string, const std::string &delimiter) {
    std::vector<std::string> result;

    const char *delimiter_c = delimiter.c_str();

    char *argument = std::strtok((char *) string.c_str(), delimiter_c);

    while (argument) {
        result.emplace_back(argument);

        argument = std::strtok(nullptr, delimiter_c);
    }

    return result;
}
