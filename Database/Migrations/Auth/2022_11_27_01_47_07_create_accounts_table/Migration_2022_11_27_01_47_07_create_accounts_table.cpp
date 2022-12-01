#include "Migration_2022_11_27_01_47_07_create_accounts_table.h"
#include "Config.h"

void Migration_2022_11_27_01_47_07_create_accounts_table::up()
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

    std::cout << "2022_11_27_01_47_07_create_accounts_table migrated" << std::endl;
}

void Migration_2022_11_27_01_47_07_create_accounts_table::down()
{
    dropTable("accounts");

    execute();

    std::cout << "2022_11_27_01_47_07_create_accounts_table dropped" << std::endl;
}

std::string Migration_2022_11_27_01_47_07_create_accounts_table::getSchemaName()
{
    return Config::Auth::Database::name;
}
