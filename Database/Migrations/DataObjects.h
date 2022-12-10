#ifndef MELLIANCORE_DATAOBJECTS_H
#define MELLIANCORE_DATAOBJECTS_H

// TODO: this approach needs rework

class PermissionObject
{
public:
    std::uint_fast64_t m_id;
    std::string m_name;

    std::map<std::string, std::map<std::string, std::int_fast32_t>> getColumnList()
    {
        return {
            {"id",   {{"position", 0}, {"type", Config::Global::data_types::type_uint64}}},
            {"name", {{"position", 1}, {"type", Config::Global::data_types::type_string}}},
        };
    }

    void setMember(
        const std::int_fast32_t &order,
        const std::int_fast64_t &int64_value,
        const std::uint_fast64_t &uint64_value,
        const double &float_value,
        const std::string &string_value,
        const bool &bool_value
    )
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

class RoleObject
{
public:
    std::uint_fast64_t m_id;
    std::string m_name;

    std::map<std::string, std::map<std::string, std::int_fast32_t>> getColumnList()
    {
        return {
            {"id",   {{"position", 0}, {"type", Config::Global::data_types::type_uint64}}},
            {"name", {{"position", 1}, {"type", Config::Global::data_types::type_string}}},
        };
    }

    void setMember(
        const std::int_fast32_t &order,
        const std::int_fast64_t &int64_value,
        const std::uint_fast64_t &uint64_value,
        const double &float_value,
        const std::string &string_value,
        const bool &bool_value
    )
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

#endif //MELLIANCORE_DATAOBJECTS_H
