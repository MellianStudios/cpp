#ifndef MELLIANCORE_MIGRATION_2022_12_08_10_00_45_CREATE_PERMISSIONS_TABLE_H
#define MELLIANCORE_MIGRATION_2022_12_08_10_00_45_CREATE_PERMISSIONS_TABLE_H

#include "Migration.h"
#include "Config.h"
#include "Support/Json.h"
#include "Support/Log/Log.h"
#include "Support/String.h"

class Migration_2022_12_08_10_00_45_create_permissions_table : public Migration
{
public:
    void up() override
    {
        createTable("permissions");

        setColumns(
            "id BIGINT UNSIGNED AUTO_INCREMENT PRIMARY KEY,"
            "name VARCHAR(255) NOT NULL"
        );

        execute();

        std::string values;

        auto data = Json::parseFile<std::vector<std::string>>("Database/Data/json/permissions");

        for (const auto &item: data) {
            values += "(\"" + item + "\")";

            if (item != data.back()) {
                values += ",";
            }
        }

        DB::unprepared("INSERT INTO `" + getSchemaName() + "`.`permissions` (`name`) VALUES " + values);

        MEL_INFO("2022_12_08_10_00_45_create_permissions_table migrated");
    }

    void down() override
    {
        dropTable("permissions");

        execute();

        MEL_INFO("2022_12_08_10_00_45_create_permissions_table dropped");
    }

    std::string getSchemaName() override
    {
        return Config::Main::Database::name;
    }

    std::string getMigrationName() override
    {
        return "Migration_2022_12_08_10_00_45_create_permissions_table";
    }
};

#endif //MELLIANCORE_MIGRATION_2022_12_08_10_00_45_CREATE_PERMISSIONS_TABLE_H
