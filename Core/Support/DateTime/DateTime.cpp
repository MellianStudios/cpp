#include <iomanip>
#include <ctime>
#include "DateTime.h"

std::string DateTime::getCurrentInFormat(const std::string &format)
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;

    oss << std::put_time(&tm, format.c_str());

    return oss.str();
}
