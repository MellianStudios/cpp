#include "Scripts/Commands/Command/Command.h"

Command::App Command::m_running_server;
std::vector<PermissionModel> Command::m_console_permissions;
std::map<std::uint8_t, std::string> Command::m_app_names = {
    {0, "api"},
    {1, "auth"},
    {2, "chat"},
    {3, "guild"},
    {4, "instance"},
    {5, "mail"},
    {6, "manager"},
    {7, "world"},
};
