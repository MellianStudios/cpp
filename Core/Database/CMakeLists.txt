add_library(MySQL Drivers/MySQL/MySQL.h Drivers/MySQL/MySQL.cpp)
target_include_directories(MySQL PUBLIC "../../Config")
target_include_directories(MySQL PUBLIC "../Models")
target_link_libraries(MySQL PUBLIC Config Model mysqlcppconn8)

add_library(DB DB/DB.h DB/DB.cpp)
target_include_directories(DB PUBLIC "Drivers")
target_link_libraries(DB PUBLIC MySQL)

add_library(Migration Migration/Migration.h Migration/Migration.cpp)
target_include_directories(Migration PUBLIC "DB")
target_link_libraries(Migration PUBLIC DB)

add_library(MigrationManager Migration/MigrationManager.h Migration/MigrationManager.cpp)
target_include_directories(MigrationManager PUBLIC "../../Database/Migrations")
target_link_libraries(MigrationManager PUBLIC Migration_2022_11_27_01_47_07_create_accounts_table)
