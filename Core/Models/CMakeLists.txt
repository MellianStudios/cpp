add_library(Model Model.h Model.cpp)
target_include_directories(Model PUBLIC "../Database/DB")
target_link_libraries(Model PUBLIC DB)
add_subdirectory(Auth)