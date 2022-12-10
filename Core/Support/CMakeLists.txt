add_library(DateTime DateTime.h)
set_target_properties(DateTime PROPERTIES LINKER_LANGUAGE CXX)

add_library(DotEnv DotEnv.h)
set_target_properties(DotEnv PROPERTIES LINKER_LANGUAGE CXX)

add_library(String String.h)
set_target_properties(String PROPERTIES LINKER_LANGUAGE CXX)

add_library(Log Log/Log.h Log/Log.cpp)
target_link_libraries(Log PUBLIC spdlog)

add_library(Json Json.h)
set_target_properties(Json PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Json PUBLIC "${PROJECT_SOURCE_DIR}/Config")
target_link_libraries(Log PUBLIC Config nlohmann_json::nlohmann_json)
