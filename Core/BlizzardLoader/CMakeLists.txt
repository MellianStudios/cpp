add_library(WDBC Drivers/WDBC/WDBC.h Drivers/WDBC/WDBC.cpp)
target_include_directories(WDBC PUBLIC "${PROJECT_SOURCE_DIR}/Config")
target_include_directories(WDBC PUBLIC "${PROJECT_SOURCE_DIR}/Core/Support/Log")
target_link_libraries(WDBC PUBLIC Config Log)

add_library(BlizzardLoader BlizzardLoader/BlizzardLoader.h)
set_target_properties(BlizzardLoader PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(BlizzardLoader PUBLIC "Drivers/WDBC")
target_link_libraries(BlizzardLoader PUBLIC WDBC)
