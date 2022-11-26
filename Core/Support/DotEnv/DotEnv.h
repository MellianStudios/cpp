#ifndef PROJECT_DOTENV_H
#define PROJECT_DOTENV_H

#include <iostream>
#include <fstream>
#include <map>

class DotEnv
{
protected:
    DotEnv();

private:
    std::fstream file;
    std::map<std::string, std::string> env;
public:
    static DotEnv &getInstance()
    {
        static DotEnv instance;

        return instance;
    }

    std::string getValue(const std::string &key, const std::string &fallback);

    DotEnv(const DotEnv &) = delete;

    DotEnv(DotEnv &&) = delete;

    DotEnv &operator=(const DotEnv &) = delete;

    DotEnv &operator=(DotEnv &&) = delete;
};

#endif //PROJECT_DOTENV_H
