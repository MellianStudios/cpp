#ifndef MELLIANCORE_MIGRATION_2022_12_08_18_38_47_CREATE_CONSOLE_PERMISSION_TABLE_H
#define MELLIANCORE_MIGRATION_2022_12_08_18_38_47_CREATE_CONSOLE_PERMISSION_TABLE_H

#include <string>
#include "Migration.h"
#include "Config.h"
#include "Database/Migrations/DataObjects.h"
#include "Support/Json.h"
#include "Support/Log/Log.h"

class Migration_2022_12_08_18_38_47_create_console_permission_table : public Migration
{
public:
    void up() override
    {
        createTable("console_permission");

        setColumns(
            "name VARCHAR(30) NOT NULL,"
            "permission_id BIGINT UNSIGNED NOT NULL"
        );

        execute();

        std::string values;

        auto data = Json::parseFile
            <std::map<std::string, std::vector<std::string>>>("Database/Data/json/console_permission");

        std::vector<PermissionObject> existing_permissions = DB::all<PermissionObject>(
            "SELECT * FROM `" + Config::Main::Database::name + "`.`permissions`"
        );

        int i = 0;

        for (const auto &[console, permissions]: data) {
            i++;

            if (permissions.empty()) {
                continue;
            }

            for (const auto &permission: permissions) {
                auto id = std::find_if(
                    existing_permissions.begin(),
                    existing_permissions.end(),
                    [&permission](const PermissionObject &object) {
                        return object.m_name == permission;
                    });

                values += "(\"" + console + "\"," + std::to_string(id->m_id) + ")";

                if (permission != permissions.back()) {
                    values += ",";
                }
            }

            if (i < data.size() - 1) {
                values += ",";
            }
        }

        DB::unprepared(
            "INSERT INTO `" + getSchemaName() + "`.`console_permission` (`name`,`permission_id`) VALUES " + values
        );

        MEL_INFO("2022_12_08_18_38_47_create_console_permission_table migrated");
    }

    void down() override
    {
        dropTable("console_permission");

        execute();

        MEL_INFO("2022_12_08_18_38_47_create_console_permission_table dropped");
    }

    std::string getSchemaName() override
    {
        return Config::Main::Database::name;
    }

    std::string getMigrationName() override
    {
        return "Migration_2022_12_08_18_38_47_create_console_permission_table";
    }
};

#endif //MELLIANCORE_MIGRATION_2022_12_08_18_38_47_CREATE_CONSOLE_PERMISSION_TABLE_H
