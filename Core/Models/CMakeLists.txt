add_library(Model Model.h)
set_target_properties(Model PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Model PUBLIC "${PROJECT_SOURCE_DIR}/Core/Database/DB")
target_link_libraries(Model PUBLIC DB QueryBuilder)

add_subdirectory(Main)
