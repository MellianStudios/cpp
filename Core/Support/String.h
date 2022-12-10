#ifndef MELLIANCORE_STRING_H
#define MELLIANCORE_STRING_H

#include <cstring>
#include <string>
#include <vector>

class String
{
public:
    [[nodiscard]] static std::vector<std::string> explode(const std::string &string, const std::string &separator)
    {
        std::vector<std::string> result;

        const char *delimiter_c = separator.c_str();

        char *argument = std::strtok((char *) string.c_str(), delimiter_c);

        while (argument) {
            result.emplace_back(argument);

            argument = std::strtok(nullptr, delimiter_c);
        }

        return result;
    }

    [[nodiscard]] static std::string implode(const std::vector<std::string> &strings, const std::string &separator)
    {
        if (strings.empty()) {
            return "";
        }

        if (strings.size() == 1) {
            return strings.at(0);
        }

        std::string result;

        for (int i = 0; i < strings.size(); i++) {
            result += strings.at(i);

            if (i < strings.size() - 1) {
                result += separator;
            }
        }

        return result;
    }

    [[nodiscard]] static std::string toUpper(std::string string)
    {
        std::transform(string.begin(), string.end(), string.begin(), ::toupper);

        return string;
    }
};

#endif //MELLIANCORE_STRING_H
