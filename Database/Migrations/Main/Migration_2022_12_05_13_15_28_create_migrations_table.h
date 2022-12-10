#ifndef MELLIANCORE_MIGRATION_2022_12_05_13_15_28_CREATE_MIGRATIONS_TABLE_H
#define MELLIANCORE_MIGRATION_2022_12_05_13_15_28_CREATE_MIGRATIONS_TABLE_H

#include "Migration.h"
#include "Config.h"
#include "Support/Log/Log.h"

class Migration_2022_12_05_13_15_28_create_migrations_table : public Migration
{
public:
    void up() override
    {
        createTable("migrations");

        setColumns(
            "id BIGINT UNSIGNED AUTO_INCREMENT PRIMARY KEY,"
            "name VARCHAR(255) NOT NULL"
        );

        execute();

        MEL_INFO("2022_12_05_13_15_28_create_migrations_table migrated");
    }

    void down() override
    {
        dropTable("migrations");

        execute();

        MEL_INFO("2022_12_05_13_15_28_create_migrations_table dropped");
    }

    std::string getSchemaName() override
    {
        return Config::Main::Database::name;
    }

    std::string getMigrationName() override
    {
        return "Migration_2022_12_05_13_15_28_create_migrations_table";
    }

};

#endif //MELLIANCORE_MIGRATION_2022_12_05_13_15_28_CREATE_MIGRATIONS_TABLE_H
