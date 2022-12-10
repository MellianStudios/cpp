#ifndef PROJECT_DOTENV_H
#define PROJECT_DOTENV_H

#include <iostream>
#include <fstream>
#include <map>

class DotEnv
{
protected:
    DotEnv()
    {
        file.open("/home/rymercyble/cpp-projects/MellianCore/.env", std::ios::in);

        std::string name;
        std::string value;
        std::string separator = "=";
        std::string line;

        if (file.is_open()) {
            while (getline(file, line)) {
                std::size_t position = line.find(separator);
                name = line.substr(0, position);
                value = line.substr(position + 1, std::string::npos);

                env.insert({name, value});
            }

            file.close();
        }
    }

private:
    std::fstream file;
    std::map<std::string, std::string> env;
public:
    static DotEnv &getInstance()
    {
        static DotEnv instance;

        return instance;
    }

    std::string getValue(const std::string &key, const std::string &fallback)
    {
        auto iterator = env.find(key);

        if (iterator != env.end()) {
            return iterator->second;
        }

        return fallback;
    }

    DotEnv(const DotEnv &) = delete;

    DotEnv(DotEnv &&) = delete;

    DotEnv &operator=(const DotEnv &) = delete;

    DotEnv &operator=(DotEnv &&) = delete;
};

#endif //PROJECT_DOTENV_H
