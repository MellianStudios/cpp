#ifndef MELLIANCORE_MIGRATION_2022_11_27_01_47_07_CREATE_ACCOUNTS_TABLE_H
#define MELLIANCORE_MIGRATION_2022_11_27_01_47_07_CREATE_ACCOUNTS_TABLE_H

#include "Migration.h"
#include "Config.h"
#include "Support/Log/Log.h"

class Migration_2022_11_27_01_47_07_create_accounts_table : public Migration
{
public:
    void up() override
    {
        createTable("accounts");

        setColumns(
            "id BIGINT UNSIGNED AUTO_INCREMENT PRIMARY KEY,"
            "username VARCHAR(30) NOT NULL,"
            "email VARCHAR(100) NOT NULL,"
            "salt BINARY(32) NOT NULL,"
            "verifier BINARY(32) NOT NULL,"
            "session_key BINARY(40),"
            "totp_secret VARBINARY(128)"
        );

        execute();

        MEL_INFO("2022_11_27_01_47_07_create_accounts_table migrated");
    }

    void down() override
    {
        dropTable("accounts");

        execute();

        MEL_INFO("2022_11_27_01_47_07_create_accounts_table dropped");
    }

    std::string getSchemaName() override
    {
        return Config::Main::Database::name;
    }

    std::string getMigrationName() override
    {
        return "Migration_2022_11_27_01_47_07_create_accounts_table";
    }
};

#endif //MELLIANCORE_MIGRATION_2022_11_27_01_47_07_CREATE_ACCOUNTS_TABLE_H
