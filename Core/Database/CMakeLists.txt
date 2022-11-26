add_library(MySQL MySQL/MySQL.h MySQL/MySQL.cpp)

target_include_directories(MySQL PUBLIC "../../Config")
target_include_directories(MySQL PUBLIC "../Models")

target_link_libraries(MySQL PUBLIC Config Model mysqlcppconn8)