add_library(CommandContract CommandContract/CommandContract.h)
set_target_properties(CommandContract PROPERTIES LINKER_LANGUAGE CXX)

add_library(AccountCommand AccountCommand/AccountCommand.h AccountCommand/AccountCommand.cpp)
target_include_directories(AccountCommand PUBLIC "${PROJECT_SOURCE_DIR}/Core")
target_link_libraries(AccountCommand PUBLIC CommandContract)

add_library(LookupCommand LookupCommand/LookupCommand.h LookupCommand/LookupCommand.cpp)
target_include_directories(LookupCommand PUBLIC "${PROJECT_SOURCE_DIR}/Core")
target_link_libraries(LookupCommand PUBLIC CommandContract)

add_library(MigrationCommand MigrationCommand/MigrationCommand.cpp MigrationCommand/MigrationCommand.h)
target_include_directories(MigrationCommand PUBLIC "${PROJECT_SOURCE_DIR}/Database/Migration")
target_include_directories(MigrationCommand PUBLIC "${PROJECT_SOURCE_DIR}/Core")
target_link_libraries(MigrationCommand PUBLIC CommandContract MigrationManager)

add_library(Command Command/Command.h Command/Command.cpp)
target_include_directories(Command PUBLIC "${PROJECT_SOURCE_DIR}/Core")
target_link_libraries(Command PUBLIC String CommandContract AccountCommand LookupCommand MigrationCommand)