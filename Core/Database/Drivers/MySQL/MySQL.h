#ifndef MELLIANCORE_MYSQL_H
#define MELLIANCORE_MYSQL_H

#include <iostream>
#include <map>
#include <vector>
#include <mysql-cppconn-8/mysqlx/xdevapi.h>
#include "Model.h"

class MySQL
{
private:
    static mysqlx::Session getSession();

public:
    static void unprepared(const std::string &raw_statement);

    static std::map<std::int64_t, std::map<std::string, std::string>> all(const std::string &raw_statement);

    static void first(
        Model &instance,
        const std::string &query,
        const std::vector<Config::Database::input_types> &bindings,
        const std::map<std::string, std::map<std::string, std::int_fast32_t>> &column_list,
        const std::vector<std::string> &select = {}
    );

    static bool tableExists(const std::string &database, const std::string &table);
};

#endif //MELLIANCORE_MYSQL_H
