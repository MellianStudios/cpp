#ifndef MELLIANCORE_MIGRATION_2022_12_08_10_19_41_CREATE_ACCOUNT_ROLE_TABLE_H
#define MELLIANCORE_MIGRATION_2022_12_08_10_19_41_CREATE_ACCOUNT_ROLE_TABLE_H

#include "Migration.h"
#include "Config.h"
#include "Support/Log/Log.h"

class Migration_2022_12_08_10_19_41_create_account_role_table : public Migration
{
public:
    void up() override
    {
        createTable("account_role");

        setColumns(
            "account_id BIGINT UNSIGNED NOT NULL,"
            "role_id BIGINT UNSIGNED NOT NULL"
        );

        execute();

        MEL_INFO("2022_12_08_10_19_41_create_account_role_table migrated");
    }

    void down() override
    {
        dropTable("account_role");

        execute();

        MEL_INFO("2022_12_08_10_19_41_create_account_role_table dropped");
    }

    std::string getSchemaName() override
    {
        return Config::Main::Database::name;
    }

    std::string getMigrationName() override
    {
        return "Migration_2022_12_08_10_19_41_create_account_role_table";
    }
};

#endif //MELLIANCORE_MIGRATION_2022_12_08_10_19_41_CREATE_ACCOUNT_ROLE_TABLE_H
