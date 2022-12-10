#include "PermissionModel.h"

const std::string PermissionModel::m_table = "permissions";

const std::map<std::string, std::map<std::string, std::int_fast32_t>> PermissionModel::m_column_list = {
    {"id",   {{"position", 0}, {"type", Config::Global::data_types::type_uint64}}},
    {"name", {{"position", 1}, {"type", Config::Global::data_types::type_string}}},
};
