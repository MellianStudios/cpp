#ifndef MELLIANCORE_JSON_H
#define MELLIANCORE_JSON_H

#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include "Config.h"

class Json
{
public:
    template<typename T>
    static T parseFile(const std::string &path)
    {
        std::fstream file(Config::Global::project_path + "/" + path + ".json");

        nlohmann::json data = nlohmann::json::parse(file);

        return data.get<T>();
    }
};

#endif //MELLIANCORE_JSON_H
