add_library(Model Model.h Model.cpp)
target_include_directories(Model PUBLIC "../Database/MySQL")
target_link_libraries(Model PUBLIC MySQL)
add_subdirectory(Auth)