#include "Migration_2022_12_05_13_15_28_create_migrations_table.h"
#include "Config.h"

void Migration_2022_12_05_13_15_28_create_migrations_table::up()
{
    createTable("migrations");

    setColumns(
        "id BIGINT UNSIGNED AUTO_INCREMENT PRIMARY KEY,"
        "name VARCHAR(255) NOT NULL"
    );

    execute();

    std::cout << "2022_12_05_13_15_28_create_migrations_table migrated" << std::endl;
}

void Migration_2022_12_05_13_15_28_create_migrations_table::down()
{
    dropTable("migrations");

    execute();

    std::cout << "2022_12_05_13_15_28_create_migrations_table migrated" << std::endl;
}

std::string Migration_2022_12_05_13_15_28_create_migrations_table::getSchemaName()
{
    return Config::Main::Database::name;
}

std::string Migration_2022_12_05_13_15_28_create_migrations_table::getMigrationName()
{
    return "Migration_2022_12_05_13_15_28_create_migrations_table";
}
