#ifndef MELLIANCORE_MODEL_H
#define MELLIANCORE_MODEL_H

#include <iostream>
#include <map>
#include <vector>
#include <variant>
#include <optional>
#include "Config.h"

class Model
{
protected:
    std::map<std::int_fast32_t, std::string> m_single;
    std::map<std::uint64_t, std::map<std::int_fast32_t, std::string>> m_multiple;
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

    void loadByColumnValue(
        const std::string &where_clause,
        const std::vector<Config::Database::input_types> &bindings,
        const std::vector<std::string> &select_columns = {}
    );
};

#endif //MELLIANCORE_MODEL_H
