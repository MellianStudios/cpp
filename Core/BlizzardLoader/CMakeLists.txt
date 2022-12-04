add_library(WDBC Drivers/WDBC/WDBC.h Drivers/WDBC/WDBC.cpp)
target_include_directories(WDBC PUBLIC "${PROJECT_SOURCE_DIR}")
target_link_libraries(WDBC PUBLIC Config)

add_library(BlizzardLoader BlizzardLoader/BlizzardLoader.h BlizzardLoader/BlizzardLoader.cpp)
target_include_directories(BlizzardLoader PUBLIC "Drivers/WDBC")
target_link_libraries(BlizzardLoader PUBLIC WDBC)