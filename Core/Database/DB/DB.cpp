#include "DB.h"
#include "MySQL/MySQL.h"

void DB::unprepared(const std::string &query)
{
    MySQL::unprepared(query);
}

void DB::first(
    Model &instance,
    const std::string &query,
    const std::vector<Config::Database::input_types> &bindings,
    const std::map<std::string, std::map<std::string, std::int_fast32_t>> &column_list,
    const std::vector<std::string> &select
)
{
    MySQL::first(instance, query, bindings, column_list, select);
}

bool DB::tableExists(const std::string &database, const std::string &table)
{
    return MySQL::tableExists(database, table);
}
