#ifndef MELLIANCORE_MIGRATION_2022_12_05_12_20_44_CREATE_ROLES_TABLE_H
#define MELLIANCORE_MIGRATION_2022_12_05_12_20_44_CREATE_ROLES_TABLE_H

#include "Migration.h"
#include "Config.h"
#include "Support/Json.h"
#include "Support/Log/Log.h"

class Migration_2022_12_05_12_20_44_create_roles_table : public Migration
{
public:
    void up() override
    {
        createTable("roles");

        setColumns(
            "id BIGINT UNSIGNED AUTO_INCREMENT PRIMARY KEY,"
            "name VARCHAR(255) NOT NULL"
        );

        execute();

        std::string values;

        auto data = Json::parseFile<std::vector<std::string>>("Database/Data/json/roles");

        for (const auto &item: data) {
            values += "(\"" + item + "\")";

            if (item != data.back()) {
                values += ",";
            }
        }

        DB::unprepared("INSERT INTO `" + getSchemaName() + "`.`roles` (`name`) VALUES " + values);

        MEL_INFO("2022_12_05_12_20_44_create_roles_table migrated");
    }

    void down() override
    {
        dropTable("roles");

        execute();

        MEL_INFO("2022_12_05_12_20_44_create_roles_table dropped");
    }

    std::string getSchemaName() override
    {
        return Config::Main::Database::name;
    }

    std::string getMigrationName() override
    {
        return "Migration_2022_12_05_12_20_44_create_roles_table";
    }
};

#endif //MELLIANCORE_MIGRATION_2022_12_05_12_20_44_CREATE_ROLES_TABLE_H
