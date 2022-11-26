add_library(Config Config.h Config.cpp)
target_include_directories(Config PUBLIC "../Core/Support/DotEnv")
target_link_libraries(Config PUBLIC DotEnv)