#ifndef MELLIANCORE_MIGRATION_2022_12_08_10_19_31_CREATE_ROLE_PERMISSION_TABLE_H
#define MELLIANCORE_MIGRATION_2022_12_08_10_19_31_CREATE_ROLE_PERMISSION_TABLE_H

#include "Migration.h"
#include "Config.h"
#include "Database/Migrations/DataObjects.h"
#include "Support/Json.h"
#include "Support/Log/Log.h"

class Migration_2022_12_08_10_19_31_create_role_permission_table : public Migration
{
public:
    void up() override
    {
        createTable("role_permission");

        setColumns(
            "role_id BIGINT UNSIGNED NOT NULL,"
            "permission_id BIGINT UNSIGNED NOT NULL"
        );

        execute();

        std::string values;

        auto data = Json::parseFile
            <std::map<std::string, std::vector<std::string>>>("Database/Data/json/role_permission");

        std::vector<PermissionObject> existing_permissions = DB::all<PermissionObject>(
            "SELECT * FROM `" + Config::Main::Database::name + "`.`permissions`"
        );

        std::vector<RoleObject> existing_roles = DB::all<RoleObject>(
            "SELECT * FROM `" + Config::Main::Database::name + "`.`roles`"
        );

        int i = 0;

        for (const auto &[role, permissions]: data) {
            i++;

            if (permissions.empty()) {
                continue;
            }

            for (const auto &permission: permissions) {
                auto existing_permission = std::find_if(
                    existing_permissions.begin(),
                    existing_permissions.end(),
                    [&permission](const PermissionObject &object) {
                        return object.m_name == permission;
                    });

                auto existing_role = std::find_if(
                    existing_roles.begin(),
                    existing_roles.end(),
                    [&role](const RoleObject &object) {
                        return object.m_name == role;
                    });

                values += "(\"" + std::to_string(existing_role->m_id) + "\"," +
                          std::to_string(existing_permission->m_id) + ")";

                if (permission != permissions.back()) {
                    values += ",";
                }
            }

            if (i < data.size() - 1) {
                values += ",";
            }
        }

        if (!values.empty()) {
            DB::unprepared(
                "INSERT INTO `" + getSchemaName() + "`.`role_permission` (`role_id`,`permission_id`) VALUES " + values
            );
        }

        MEL_INFO("2022_12_08_10_19_31_create_role_permission_table migrated");
    }

    void down() override
    {
        dropTable("role_permission");

        execute();

        MEL_INFO("2022_12_08_10_19_31_create_role_permission_table dropped");
    }

    std::string getSchemaName() override
    {
        return Config::Main::Database::name;
    }

    std::string getMigrationName() override
    {
        return "Migration_2022_12_08_10_19_31_create_role_permission_table";
    }
};

#endif //MELLIANCORE_MIGRATION_2022_12_08_10_19_31_CREATE_ROLE_PERMISSION_TABLE_H
