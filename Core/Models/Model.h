#ifndef MELLIANCORE_MODEL_H
#define MELLIANCORE_MODEL_H

#include <map>
#include <optional>
#include <string>
#include <variant>
#include <vector>
#include "Config.h"
#include "DB.h"
#include "Model.h"

class Model
{
protected:
    std::map<std::int_fast32_t, std::string> m_single;
    std::map<std::uint64_t, std::map<std::int_fast32_t, std::string>> m_multiple;

    template<typename T>
    void loadByColumnValue(
        const std::string &where_clause,
        const std::vector<Config::Database::input_types> &bindings,
        const std::vector<std::string> &select_columns = {}
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

        DB::first<T>(statement, bindings, getColumnList(), select_columns);
    }

    template<typename T>
    std::vector<T> loadAll()
    {
        std::string query = "SELECT * FROM " + getDatabaseName() + "." + getTableName();

        return DB::all<T>(query);
    }

public:
    virtual void setMember(
        const std::int_fast32_t &order,
        const std::int_fast64_t &int64_value,
        const std::uint_fast64_t &uint64_value,
        const double &float_value,
        const std::string &string_value,
        const bool &bool_value
    ) = 0;

    virtual std::string getTableName() = 0;

    virtual std::string getDatabaseName() = 0;

    virtual std::map<std::string, std::map<std::string, std::int_fast32_t>> getColumnList() = 0;
};

#endif //MELLIANCORE_MODEL_H
