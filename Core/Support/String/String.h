#ifndef MELLIANCORE_STRING_H
#define MELLIANCORE_STRING_H

#include <vector>

class String
{
public:
    [[nodiscard]]static std::vector<std::string> explode(const std::string &string, const std::string &delimiter);

    [[nodiscard]]static std::string toUpper(std::string string);
};

#endif //MELLIANCORE_STRING_H
