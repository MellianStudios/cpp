#include <iostream>
#include <vector>
#include "Config.h"
#include "Model.h"
#include "DB.h"

void Model::loadByColumnValue(
    const std::string &where_clause,
    const std::vector<Config::Database::input_types> &bindings,
    const std::vector<std::string> &select_columns
)
{
    std::string select;

    std::int_fast32_t select_count = select_columns.size();

    if (!select_columns.empty()) {
        for (std::int_fast32_t i; i < select_count; i++) {
            select += "`" + select_columns[i] + "`";

            if (select_count > 1 && i < select_count) {
                select += ",";
            }
        }
    } else {
        select = "*";
    }

    std::string statement =
        "SELECT " + select + " FROM " + getDatabaseName() + "." + getTableName() + " WHERE " + where_clause;

    DB::first(*this, statement, bindings, getColumnList(), select_columns);
}
