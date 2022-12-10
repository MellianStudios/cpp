add_library(CommandContract CommandContract.h)
set_target_properties(CommandContract PROPERTIES LINKER_LANGUAGE CXX)

add_library(AccountCommand AccountCommand.h)
set_target_properties(AccountCommand PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(AccountCommand PUBLIC "${PROJECT_SOURCE_DIR}/Core")
target_link_libraries(AccountCommand PUBLIC CommandContract)

add_library(LookupCommand LookupCommand.h)
set_target_properties(LookupCommand PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(LookupCommand PUBLIC "${PROJECT_SOURCE_DIR}/Core")
target_link_libraries(LookupCommand PUBLIC CommandContract)

add_library(MigrationCommand MigrationCommand.h)
set_target_properties(MigrationCommand PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(MigrationCommand PUBLIC "${PROJECT_SOURCE_DIR}/Database/Migration")
target_include_directories(MigrationCommand PUBLIC "${PROJECT_SOURCE_DIR}/Core")
target_link_libraries(MigrationCommand PUBLIC CommandContract MigrationManager)

add_library(Command Command/Command.h Command/Command.cpp)
set_target_properties(Command PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Command PUBLIC "${PROJECT_SOURCE_DIR}/Core")
target_link_libraries(Command PUBLIC String Log DB QueryBuilder PermissionModel ConsolePermissionModel CommandContract AccountCommand LookupCommand MigrationCommand)
