#ifndef MELLIANCORE_PERMISSIONMODEL_H
#define MELLIANCORE_PERMISSIONMODEL_H

#include "Config.h"
#include "Models/Model.h"
#include "Support/Log/Log.h"

class PermissionModel : public Model
{
private:
    static const std::string m_table;
    static const std::map<std::string, std::map<std::string, std::int_fast32_t>> m_column_list;

public:
    std::uint64_t m_id;
    std::string m_name;

    std::string getTableName() override
    {
        return PermissionModel::m_table;
    }

    std::string getDatabaseName() override
    {
        return Config::Main::Database::name;
    }

    std::map<std::string, std::map<std::string, std::int_fast32_t>> getColumnList() override
    {
        return PermissionModel::m_column_list;
    }

    static std::string getTableNameWithDBPrefix()
    {
        return Config::Main::Database::name + "." + PermissionModel::m_table;
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
                m_id = uint64_value;
                break;
            case 1:
                m_name = string_value;
                break;
            default:
                MEL_ERROR("column of position {0} was not found", order);
        }
    }
};

#endif //MELLIANCORE_PERMISSIONMODEL_H
