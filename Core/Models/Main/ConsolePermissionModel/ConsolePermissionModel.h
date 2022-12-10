#ifndef MELLIANCORE_CONSOLEPERMISSIONMODEL_H
#define MELLIANCORE_CONSOLEPERMISSIONMODEL_H

#include "Config.h"
#include "Models/Model.h"
#include "Support/Log/Log.h"

class ConsolePermissionModel : public Model
{
private:
    static const std::string m_table;
    static const std::map<std::string, std::map<std::string, std::int_fast32_t>> m_column_list;

public:
    std::string m_name;
    std::uint64_t m_permission_id;

    std::string getTableName() override
    {
        return ConsolePermissionModel::m_table;
    }

    std::string getDatabaseName() override
    {
        return Config::Main::Database::name;
    }

    std::map<std::string, std::map<std::string, std::int_fast32_t>> getColumnList() override
    {
        return ConsolePermissionModel::m_column_list;
    }

    static std::string getTableNameWithDBPrefix()
    {
        return Config::Main::Database::name + "." + ConsolePermissionModel::m_table;
    }

    void setMember(
        const std::int_fast32_t &order,
        const std::int_fast64_t &int64_value,
        const std::uint_fast64_t &uint64_value,
        const double &float_value,
        const std::string &string_value,
        const bool &bool_value
    ) override
    {
        switch (order) {
            case 0:
                m_name = string_value;
                break;
            case 1:
                m_permission_id = uint64_value;
                break;
            default:
                MEL_ERROR("column of position {0} was not found", order);
        }
    }
};

#endif //MELLIANCORE_CONSOLEPERMISSIONMODEL_H
