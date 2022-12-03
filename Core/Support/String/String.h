#ifndef MELLIANCORE_STRING_H
#define MELLIANCORE_STRING_H

#include <vector>

class String
{
public:
    static std::vector<std::string> explode(const std::string &string, const std::string &delimiter);
};

#endif //MELLIANCORE_STRING_H
