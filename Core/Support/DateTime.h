#ifndef MELLIANCORE_DATETIME_H
#define MELLIANCORE_DATETIME_H

#include <string>

class DateTime
{
public:
    static std::string getCurrentInFormat(const std::string &format)
    {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        std::ostringstream oss;

        oss << std::put_time(&tm, format.c_str());

        return oss.str();
    }
};

#endif //MELLIANCORE_DATETIME_H
