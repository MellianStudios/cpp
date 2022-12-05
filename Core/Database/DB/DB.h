#ifndef MELLIANCORE_DB_H
#define MELLIANCORE_DB_H

#include <iostream>
#include <map>
#include <vector>
#include "Model.h"

class DB
{
public:
    static void unprepared(const std::string &query);

    static void first(
        Model &instance,
        const std::string &query,
        const std::vector<Config::Database::input_types> &bindings,
        const std::map<std::string, std::map<std::string, std::int_fast32_t>> &column_list,
        const std::vector<std::string> &select = {}
    );

    static bool tableExists(const std::string &database, const std::string &table);
};

#endif //MELLIANCORE_DB_H
