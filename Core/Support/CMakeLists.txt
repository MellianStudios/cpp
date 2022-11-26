add_library(DotEnv DotEnv/DotEnv.h DotEnv/DotEnv.cpp)
target_include_directories(DotEnv PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/DotEnv/")