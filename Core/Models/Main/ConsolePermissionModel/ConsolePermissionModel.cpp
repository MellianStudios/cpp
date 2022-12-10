#include "ConsolePermissionModel.h"

const std::string ConsolePermissionModel::m_table = "console_permission";

const std::map<std::string, std::map<std::string, std::int_fast32_t>> ConsolePermissionModel::m_column_list = {
    {"name",          {{"position", 0}, {"type", Config::Global::data_types::type_string}}},
    {"permission_id", {{"position", 1}, {"type", Config::Global::data_types::type_uint64}}},
};
