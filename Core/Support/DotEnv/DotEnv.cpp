#include <iostream>
#include <string>
#include <iterator>
#include "DotEnv.h"

DotEnv::DotEnv()
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

std::string DotEnv::getValue(const std::string &key, const std::string &fallback)
{
    auto iterator = env.find(key);

    if (iterator != env.end()) {
        return iterator->second;
    }

    return fallback;
}


