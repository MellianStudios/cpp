add_library(CommandContract CommandContract/CommandContract.h)
set_target_properties(CommandContract PROPERTIES LINKER_LANGUAGE CXX)

add_library(AccountCommand AccountCommand/AccountCommand.h AccountCommand/AccountCommand.cpp)
target_link_libraries(AccountCommand PUBLIC CommandContract)

add_library(LookupCommand LookupCommand/LookupCommand.h LookupCommand/LookupCommand.cpp)
target_link_libraries(LookupCommand PUBLIC CommandContract)

add_library(MigrateCommand MigrateCommand/MigrateCommand.cpp MigrateCommand/MigrateCommand.h)
target_include_directories(MigrateCommand PUBLIC "../../Database/Migration")
target_link_libraries(MigrateCommand PUBLIC CommandContract MigrationManager)

add_library(Command Command/Command.h Command/Command.cpp)
target_include_directories(Command PUBLIC "../../")
target_link_libraries(Command PUBLIC String CommandContract AccountCommand LookupCommand MigrateCommand)