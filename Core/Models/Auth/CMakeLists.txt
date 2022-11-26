add_library(Account Account/Account.h Account/Account.cpp)
target_include_directories(Account PUBLIC "${PROJECT_SOURCE_DIR}/Core/Models")
target_link_libraries(Account PUBLIC Model)