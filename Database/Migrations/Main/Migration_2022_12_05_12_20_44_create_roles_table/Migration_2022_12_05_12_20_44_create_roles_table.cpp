#include "Migration_2022_12_05_12_20_44_create_roles_table.h"
#include "Config.h"

void Migration_2022_12_05_12_20_44_create_roles_table::up()
{
    createTable("roles");

    setColumns("id BIGINT UNSIGNED AUTO_INCREMENT PRIMARY KEY");

    execute();

    std::cout << "2022_12_05_12_20_44_create_roles_table migrated" << std::endl;
}

void Migration_2022_12_05_12_20_44_create_roles_table::down()
{
    dropTable("roles");

    execute();

    std::cout << "2022_12_05_12_20_44_create_roles_table migrated" << std::endl;
}

std::string Migration_2022_12_05_12_20_44_create_roles_table::getSchemaName()
{
    return Config::Main::Database::name;
}

std::string Migration_2022_12_05_12_20_44_create_roles_table::getMigrationName()
{
    return "Migration_2022_12_05_12_20_44_create_roles_table";
}

