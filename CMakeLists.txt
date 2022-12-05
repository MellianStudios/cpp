cmake_minimum_required(VERSION 3.22)
project(MellianCore VERSION 0.0.0)
set(CMAKE_CXX_STANDARD 20)

SET(SERVER_TARGET_PATH)
if (NOT SERVER_TARGET_PATH)
    message(FATAL_ERROR "SERVER_TARGET_PATH must be defined")
endif ()

add_subdirectory(Dependencies)
add_subdirectory(Config)
add_subdirectory(Core)
add_subdirectory(Database)
add_subdirectory(Servers)
