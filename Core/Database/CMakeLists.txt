add_library(MySQL Drivers/MySQL/MySQL.h)
set_target_properties(MySQL PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(MySQL PUBLIC "${PROJECT_SOURCE_DIR}/Config")
target_link_libraries(MySQL PUBLIC Config mysqlcppconn8)

add_library(DB DB/DB.h)
set_target_properties(DB PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(DB PUBLIC "Drivers")
target_link_libraries(DB PUBLIC MySQL)

add_library(Migration Migration/Migration.h)
set_target_properties(Migration PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Migration PUBLIC "DB")
target_link_libraries(Migration PUBLIC DB)

add_library(QueryBuilder QueryBuilder/QueryBuilder.h)
set_target_properties(QueryBuilder PROPERTIES LINKER_LANGUAGE CXX)

add_library(MigrationManager Migration/MigrationManager.h)
set_target_properties(MigrationManager PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(MigrationManager PUBLIC "${PROJECT_SOURCE_DIR}/")
target_link_libraries(MigrationManager PUBLIC String DateTime Config
        Migration_2022_12_05_13_15_28_create_migrations_table
        Migration_2022_11_27_01_47_07_create_accounts_table
        Migration_2022_12_05_12_20_44_create_roles_table
        Migration_2022_12_08_10_00_45_create_permissions_table
        Migration_2022_12_08_10_19_31_create_role_permission_table
        Migration_2022_12_08_10_19_41_create_account_role_table
        Migration_2022_12_08_18_38_47_create_console_permission_table
        )
