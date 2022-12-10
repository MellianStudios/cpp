#ifndef MELLIANCORE_DB_H
#define MELLIANCORE_DB_H

#include <map>
#include <string>
#include <vector>
#include "MySQL/MySQL.h"

class DB
{
public:
    static void unprepared(const std::string &query)
    {
        MySQL::unprepared(query);
    }

    template<typename T>
    static void first(
        const std::string &query,
        const std::vector<Config::Database::input_types> &bindings,
        const std::map<std::string, std::map<std::string, std::int_fast32_t>> &column_list,
        const std::vector<std::string> &select = {}
    )
    {
        MySQL::first<T>(query, bindings, column_list, select);
    }

    static bool tableExists(const std::string &database, const std::string &table)
    {
        return MySQL::tableExists(database, table);
    }

    template<typename T>
    static std::vector<T> all(const std::string &query)
    {
        return MySQL::all<T>(query);
    }
};

#endif //MELLIANCORE_DB_H
