add_library(AccountModel AccountModel/AccountModel.h AccountModel/AccountModel.cpp)
target_include_directories(AccountModel PUBLIC "${PROJECT_SOURCE_DIR}/Core")
target_link_libraries(AccountModel PUBLIC Model Log QueryBuilder)

add_library(PermissionModel PermissionModel/PermissionModel.h PermissionModel/PermissionModel.cpp)
target_include_directories(PermissionModel PUBLIC "${PROJECT_SOURCE_DIR}/Core")
target_link_libraries(PermissionModel PUBLIC Model Log QueryBuilder)

add_library(ConsolePermissionModel ConsolePermissionModel/ConsolePermissionModel.h ConsolePermissionModel/ConsolePermissionModel.cpp)
target_include_directories(ConsolePermissionModel PUBLIC "${PROJECT_SOURCE_DIR}/Core")
target_link_libraries(ConsolePermissionModel PUBLIC Model Log QueryBuilder)
